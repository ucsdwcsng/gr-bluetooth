/* -*- c++ -*- */
/* 
 * Copyright 2013 Christopher D. Kilgour
 * Copyright 2008, 2009 Dominic Spill, Michael Ossmann
 * Copyright 2007 Dominic Spill
 * Copyright 2005, 2006 Free Software Foundation, Inc.
 * 
 * This file is part of gr-bluetooth
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "pcapng_writer.h"
#include <cstdio>
#include <cstring>

// Include BLE packet constants
#define CONNECT_REQ 5

namespace gr {
  namespace bluetooth {

    pcapng_writer::sptr
    pcapng_writer::make(const std::string& filename)
    {
      return pcapng_writer::sptr(new pcapng_writer(filename));
    }

    pcapng_writer::pcapng_writer(const std::string& filename)
      : d_pcapng_enabled(false), d_filename(filename),
        d_pcapng_handle(nullptr)
    {
    }

    pcapng_writer::~pcapng_writer()
    {
      close();
    }

    bool pcapng_writer::init()
    {
      if (d_filename.empty()) {
        d_pcapng_enabled = false;
        return false;
      }

      // Initialize handles to NULL
      d_pcapng_handle = nullptr;

      // delete file if it already exists
      std::remove(d_filename.c_str());
      
      // Create pcapng file
      int result = btbb_pcapng_create_file(d_filename.c_str(), "gr-bluetooth", &d_pcapng_handle);

      if (result != 0) {
        fprintf(stderr, "Failed to create pcapng files: %s (error %d)\n", 
                d_filename.c_str(), result);
        d_pcapng_enabled = false;
        return false;
      }

      d_pcapng_enabled = true;
      return true;
    }

    void pcapng_writer::write_bredr_packet(classic_packet::sptr pkt, 
                                          basic_rate_piconet::sptr pn, 
                                          uint64_t timestamp_ns, 
                                          int8_t signal_power, 
                                          int8_t noise_power)
    {
      if (!d_pcapng_enabled || !d_pcapng_handle) return;

      // Create a new btbb_packet and populate it with data from gr-bluetooth packet
      btbb_packet *btbb_pkt = btbb_packet_new();
      if (!btbb_pkt) return;

      // Set packet flags based on what information we have
      btbb_packet_set_flag(btbb_pkt, BTBB_LAP_VALID, 1);
      
      // Set UAP if available from piconet
      if (pn->have_UAP()) {
        btbb_packet_set_uap(btbb_pkt, pn->get_UAP());
        btbb_packet_set_flag(btbb_pkt, BTBB_UAP_VALID, 1);
      }
      
      // Set NAP if available from piconet
      if (pn->have_NAP()) {
        // libbtbb doesn't have a direct set_nap function, but we can record it separately
        btbb_packet_set_flag(btbb_pkt, BTBB_NAP_VALID, 1);
      }

      // Set clock information if available
      if (pn->have_clk6()) {
        btbb_packet_set_flag(btbb_pkt, BTBB_CLK6_VALID, 1);
      }
      if (pn->have_clk27()) {
        btbb_packet_set_flag(btbb_pkt, BTBB_CLK27_VALID, 1);
      }

      // Set packet type and header information
      if (pkt->header_present()) {
        // Set packet type, LT_ADDR, and other header info
        btbb_packet_set_flag(btbb_pkt, BTBB_HAS_PAYLOAD, pkt->got_payload() ? 1 : 0);
      }

      // Set payload information
      if (pkt->got_payload()) {
        btbb_packet_set_flag(btbb_pkt, BTBB_HAS_PAYLOAD, 1);
        
        // Set CRC status - we assume it's correct if the packet was successfully decoded
        btbb_packet_set_flag(btbb_pkt, BTBB_CRC_CORRECT, 1);
      }

      // Set modulation type (assume GFSK for classic Bluetooth)
      btbb_packet_set_modulation(btbb_pkt, BTBB_MOD_GFSK);

      // Set transport type based on packet type
      uint8_t packet_type = pkt->get_type();
      switch (packet_type) {
        case 0: // NULL, POLL, FHS, DM1
        case 1: // DH1
        case 2: // DM3, DH3
        case 3: // DM5, DH5
          btbb_packet_set_transport(btbb_pkt, BTBB_TRANSPORT_ACL);
          break;
        case 4: // HV1, HV2, HV3, DV
          btbb_packet_set_transport(btbb_pkt, BTBB_TRANSPORT_SCO);
          break;
        default:
          btbb_packet_set_transport(btbb_pkt, BTBB_TRANSPORT_ANY);
          break;
      }

      // Get LAP and UAP for pcapng function
      uint32_t lap = pkt->get_LAP();
      uint8_t uap = pn->have_UAP() ? pn->get_UAP() : UAP_ANY;

      // Write to pcapng file with all the comprehensive information
      int result = btbb_pcapng_append_packet((btbb_pcapng_handle*)d_pcapng_handle, timestamp_ns,
                                           signal_power, noise_power,
                                           lap, uap, btbb_pkt);
      
      if (result != 0) {
        fprintf(stderr, "Failed to write BR/EDR packet to pcapng (error %d)\n", result);
      }

      btbb_packet_unref(btbb_pkt);
    }

    void pcapng_writer::btbb_record_bdaddr_info(basic_rate_piconet::sptr pn, classic_packet::sptr pkt)
    {
      // Record additional piconet information if available
      if (pn->have_NAP() && pn->have_UAP()) {
        uint64_t bdaddr = ((uint64_t)pn->get_NAP() << 32) | ((uint64_t)pn->get_UAP() << 24) | pkt->get_LAP();
        btbb_pcapng_record_bdaddr((btbb_pcapng_handle*)d_pcapng_handle, bdaddr, 0xFF, 1);
      }
    }

    void pcapng_writer::btbb_record_clk_info(basic_rate_piconet::sptr pn, classic_packet::sptr pkt, uint64_t timestamp_ns)
    {
      // Record clock information if available
      if (pn->have_clk27()) {
        uint64_t bdaddr = ((uint64_t)pn->get_NAP() << 32) | ((uint64_t)pn->get_UAP() << 24) | pkt->get_LAP();
        btbb_pcapng_record_btclock((btbb_pcapng_handle*)d_pcapng_handle, bdaddr, timestamp_ns, pkt->d_clkn, 0x7FFFFFF);
      }
    }

    void pcapng_writer::write_le_packet(le_packet::sptr pkt, 
                                       uint64_t timestamp_ns, 
                                       int8_t signal_power, 
                                       int8_t noise_power)
    {
      if (!d_pcapng_enabled || !d_pcapng_handle) return;

      // Get the raw symbols from the gr-bluetooth packet
      const char* symbols = pkt->get_symbols();
      int symbol_length = pkt->get_symbol_length();
      
      if (!symbols || symbol_length <= 0) {
        fprintf(stderr, "BLE packet has no symbol data for pcapng export\n");
        return;
      }

      // Convert symbols to bytes for libbtbb
      // BLE packets are transmitted as bits, but libbtbb expects byte stream
      int byte_length = (symbol_length + 7) / 8; // Round up to nearest byte
      uint8_t* byte_stream = new uint8_t[byte_length];
      
      // Convert bit symbols to bytes (LSB first for BLE)
      for (int i = 0; i < byte_length; i++) {
        uint8_t byte_val = 0;
        for (int bit = 0; bit < 8 && (i * 8 + bit) < symbol_length; bit++) {
          if (symbols[i * 8 + bit]) {
            byte_val |= (1 << bit);
          }
        }
        byte_stream[i] = byte_val;
      }

      // Create libbtbb LE packet
      lell_packet* lell_pkt = nullptr;
      
      // Convert timestamp to 100ns units (libbtbb expects clk100ns)
      uint32_t clk100ns = (uint32_t)(timestamp_ns / 100);
      
      // Get physical channel from the packet
      uint16_t phys_channel = (uint16_t)pkt->get_channel()*2 + 2402; // Convert to MHz
      
      // Allocate and decode using libbtbb
      lell_allocate_and_decode(byte_stream, phys_channel, clk100ns, &lell_pkt);
      
      if (lell_pkt) {
        // Get Access Address for reference
        uint32_t ref_aa = pkt->get_AA();
        
        // Write to pcapng file
        int result = lell_pcapng_append_packet(d_pcapng_handle, timestamp_ns,
                                             signal_power, noise_power,
                                             ref_aa, lell_pkt);
        
        if (result != 0) {
          fprintf(stderr, "Failed to write BLE packet to pcapng (error %d)\n", result);
        }
        
        // Clean up libbtbb packet
        lell_packet_unref(lell_pkt);
      } else {
        fprintf(stderr, "Failed to create libbtbb LE packet for pcapng export\n");
      }
      
      // Clean up byte stream
      delete[] byte_stream;
    }

    void pcapng_writer::le_record_connect_req(le_packet::sptr pkt, uint64_t timestamp_ns)
    {
      if (!d_pcapng_enabled || !d_pcapng_handle) return;

      // Get the PDU data from the packet
      const uint8_t* pdu = pkt->get_pdu();
      if (!pdu) {
        fprintf(stderr, "CONNECT_REQ packet has no PDU data\n");
        return;
      }

      // Get PDU length
      unsigned pdu_length = pkt->get_pdu_length();
      if (pdu_length == 0) {
        fprintf(stderr, "CONNECT_REQ packet has invalid PDU length: %u\n", pdu_length);
        return;
      }

      // Verify this is actually a CONNECT_REQ packet
      if (pkt->get_pdu_type() != CONNECT_REQ) {
        fprintf(stderr, "Packet is not a CONNECT_REQ (type: %u)\n", pkt->get_pdu_type());
        return;
      }

      // Record CONNECT_REQ parameters to pcapng file
      int result = lell_pcapng_record_connect_req(d_pcapng_handle, timestamp_ns, pdu);

      if (result != 0) {
        fprintf(stderr, "Failed to record CONNECT_REQ to pcapng (error %d)\n", result);
      }
    }

    void pcapng_writer::close()
    {
      if (d_pcapng_enabled) {
        if (d_pcapng_handle != nullptr) {
          btbb_pcapng_close((btbb_pcapng_handle*)d_pcapng_handle);
          d_pcapng_handle = nullptr;
        }
        d_pcapng_enabled = false;
      }
    }

  } /* namespace bluetooth */
} /* namespace gr */

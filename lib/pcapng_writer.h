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

#ifndef INCLUDED_BLUETOOTH_PCAPNG_WRITER_H
#define INCLUDED_BLUETOOTH_PCAPNG_WRITER_H

#include <bluetooth/api.h>
#include <bluetooth/packet.h>
#include <bluetooth/piconet.h>
#include <cstring>
#include <sys/time.h>
#include <vector>
#include <string>
#include <memory>

// Include libbtbb header for pcapng support
#include <btbb.h>

namespace gr {
  namespace bluetooth {

    /*!
     * \brief PCAPNG file writer for Bluetooth packets
     * \ingroup gr_bluetooth
     */
    class BLUETOOTH_API pcapng_writer 
    {
    private:
      bool d_pcapng_enabled;
      std::string d_filename;

      btbb_pcapng_handle* d_pcapng_handle;

    public:
      typedef std::shared_ptr<pcapng_writer> sptr;

      /*!
       * \brief Create a new PCAPNG writer instance
       * \param filename Base filename for pcapng files
       */
      static sptr make(const std::string& filename);

      pcapng_writer(const std::string& filename);
      ~pcapng_writer();

      /*!
       * \brief Initialize PCAPNG writer
       * \return true if initialization successful
       */
      bool init();

      /*!
       * \brief Check if PCAPNG writer is enabled and ready
       */
      bool is_enabled() const { return d_pcapng_enabled; }

      /*!
       * \brief Write BR/EDR packet to pcapng file
       * \param pkt Classic packet to write
       * \param pn Piconet information  
       * \param timestamp_ns Timestamp in nanoseconds
       * \param signal_power Signal power in dBm
       * \param noise_power Noise power in dBm
       */
      void write_bredr_packet(classic_packet::sptr pkt, 
                             basic_rate_piconet::sptr pn, 
                             uint64_t timestamp_ns, 
                             int8_t signal_power, 
                             int8_t noise_power);

      /*!
       * \brief Record Bluetooth address information to pcapng file
       * \param pn Piconet information
       * \param pkt Classic packet
       */
      void btbb_record_bdaddr_info(basic_rate_piconet::sptr pn, classic_packet::sptr pkt);

      /*!
       * \brief Record Bluetooth clock information to pcapng file
       * \param pn Piconet information
       * \param pkt Classic packet
       * \param timestamp_ns Timestamp in nanoseconds
       */
      void btbb_record_clk_info(basic_rate_piconet::sptr pn, classic_packet::sptr pkt, uint64_t timestamp_ns);

      /*!
       * \brief Write BLE packet to pcapng file
       * \param pkt BLE packet to write
       * \param timestamp_ns Timestamp in nanoseconds
       * \param signal_power Signal power in dBm
       * \param noise_power Noise power in dBm
       */
      void write_le_packet(le_packet::sptr pkt, 
                          uint64_t timestamp_ns, 
                          int8_t signal_power, 
                          int8_t noise_power);

      /*!
       * \brief Record BLE CONNECT_REQ parameters to pcapng file
       */
      void le_record_connect_req(le_packet::sptr pkt, uint64_t timestamp_ns);
      
      /*!
       * \brief Close PCAPNG files
       */
      void close();
    };

  } // namespace bluetooth
} // namespace gr

#endif /* INCLUDED_BLUETOOTH_PCAPNG_WRITER_H */

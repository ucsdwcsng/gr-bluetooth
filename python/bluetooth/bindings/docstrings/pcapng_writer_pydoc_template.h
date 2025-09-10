/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#include "pydoc_macros.h"
#define D(...) DOC(gr,bluetooth, __VA_ARGS__ )
/*
  This file contains placeholders for docstrings for the Python bindings.
  Do not edit! These were automatically extracted during the binding process
  and will be overwritten during the build process
 */


 
 static const char *__doc_gr_bluetooth_pcapng_writer = R"doc(PCAPNG file writer for Bluetooth packets)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_pcapng_writer_0 = R"doc()doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_pcapng_writer_1 = R"doc()doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_make = R"doc(Create a new PCAPNG writer instance
Args:
    filename: Base filename for pcapng files)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_init = R"doc(Initialize PCAPNG writer
Returns:
    True if initialization successful)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_is_enabled = R"doc(Check if PCAPNG writer is enabled and ready)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_write_bredr_packet = R"doc(Write BR/EDR packet to pcapng file
Args:
    pkt: Classic packet to write
    pn: Piconet information  
    timestamp_ns: Timestamp in nanoseconds
    signal_power: Signal power in dBm
    noise_power: Noise power in dBm)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_write_le_packet = R"doc(Write BLE packet to pcapng file
Args:
    pkt: BLE packet to write
    timestamp_ns: Timestamp in nanoseconds
    signal_power: Signal power in dBm
    noise_power: Noise power in dBm)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_btbb_record_bdaddr_info = R"doc(Record Bluetooth address information to pcapng file
Args:
    pn: Piconet information
    pkt: Classic packet)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_btbb_record_clk_info = R"doc(Record Bluetooth clock information to pcapng file
Args:
    pn: Piconet information
    pkt: Classic packet
    timestamp_ns: Timestamp in nanoseconds)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_le_record_connect_req = R"doc(Record BLE CONNECT_REQ parameters to pcapng file
Args:
    pkt: BLE packet
    timestamp_ns: Timestamp in nanoseconds)doc";


 static const char *__doc_gr_bluetooth_pcapng_writer_close = R"doc(Close PCAPNG files)doc";

  
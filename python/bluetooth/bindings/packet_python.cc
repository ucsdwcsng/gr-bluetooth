/*
 * Copyright 2022 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(packet.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(7e7aead1a9d78212759a54210dda99ca)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <bluetooth/packet.h>
// pydoc.h is automatically generated in the build directory
#include <packet_pydoc.h>

void bind_packet(py::module& m)
{

    using packet    = ::gr::bluetooth::packet;
    using classic_packet    = ::gr::bluetooth::classic_packet;
    using le_packet    = ::gr::bluetooth::le_packet;


    py::class_<packet,
        std::shared_ptr<packet>>(m, "packet", D(packet))

        .def_static("sniff_packet",&packet::sniff_packet,
            py::arg("stream"),
            py::arg("stream_length"),
            py::arg("freq"),
            py::arg("fmt"),
            D(packet,sniff_packet)
        )


        
        .def_static("reverse",&packet::reverse,       
            py::arg("byte"),
            D(packet,reverse)
        )


        
        .def_static("convert_to_grformat",&packet::convert_to_grformat,       
            py::arg("input"),
            py::arg("output"),
            D(packet,convert_to_grformat)
        )


        
        .def_static("air_to_host8",&packet::air_to_host8,       
            py::arg("air_order"),
            py::arg("bits"),
            D(packet,air_to_host8)
        )


        
        .def_static("air_to_host16",&packet::air_to_host16,       
            py::arg("air_order"),
            py::arg("bits"),
            D(packet,air_to_host16)
        )


        
        .def_static("air_to_host32",&packet::air_to_host32,       
            py::arg("air_order"),
            py::arg("bits"),
            D(packet,air_to_host32)
        )


        
        .def_static("host_to_air",&packet::host_to_air,       
            py::arg("host_order"),
            py::arg("air_order"),
            py::arg("bits"),
            D(packet,host_to_air)
        )


        
        .def("get_whitened",&packet::get_whitened,       
            D(packet,get_whitened)
        )


        
        .def("set_whitened",&packet::set_whitened,       
            py::arg("whitened"),
            D(packet,set_whitened)
        )


        
        .def("get_payload_length",&packet::get_payload_length,       
            D(packet,get_payload_length)
        )


        
        .def("got_payload",&packet::got_payload,       
            D(packet,got_payload)
        )


        
        .def("get_type",&packet::get_type,       
            D(packet,get_type)
        )


        
        .def("decode",&packet::decode,       
            D(packet,decode)
        )


        
        .def("decode_header",&packet::decode_header,       
            D(packet,decode_header)
        )


        
        .def("decode_payload",&packet::decode_payload,       
            D(packet,decode_payload)
        )


        
        .def("print",&packet::print,       
            D(packet,print)
        )


        
        .def("tun_format",&packet::tun_format,       
            D(packet,tun_format)
        )


        
        .def("header_present",&packet::header_present,       
            D(packet,header_present)
        )


        
        .def("get_channel",&packet::get_channel,       
            D(packet,get_channel)
        )

        ;


    py::class_<classic_packet, gr::bluetooth::packet,
        std::shared_ptr<classic_packet>>(m, "classic_packet", D(classic_packet))

        // NOTE: issue with overloaded functions, automated tools don't
        // generate correct code
        // https://lists.gnu.org/archive/html/discuss-gnuradio/2021-01/msg00206.html
        .def(py::init((std::shared_ptr<classic_packet>(*)(char*, int)) &
                      classic_packet::make),
             py::arg("stream"),
             py::arg("length"),
             D(classic_packet, make, 0))


        .def(py::init((std::shared_ptr<classic_packet>(*)(char*, int, uint32_t, double)) &
                      classic_packet::make),
             py::arg("stream"),
             py::arg("length"),
             py::arg("clkn"),
             py::arg("freq"),
             D(classic_packet, make, 1))
        






        
        .def_static("sniff_ac",&classic_packet::sniff_ac,       
            py::arg("stream"),
            py::arg("stream_length"),
            D(classic_packet,sniff_ac)
        )


        
        .def_static("lfsr",&classic_packet::lfsr,       
            py::arg("data"),
            py::arg("length"),
            py::arg("k"),
            py::arg("g"),
            D(classic_packet,lfsr)
        )


        
        .def_static("acgen",&classic_packet::acgen,       
            py::arg("LAP"),
            D(classic_packet,acgen)
        )


        
        .def_static("unfec13",&classic_packet::unfec13,       
            py::arg("input"),
            py::arg("output"),
            py::arg("length"),
            D(classic_packet,unfec13)
        )


        
        .def_static("unfec23",&classic_packet::unfec23,       
            py::arg("input"),
            py::arg("length"),
            D(classic_packet,unfec23)
        )


        
        .def_static("check_ac",&classic_packet::check_ac,       
            py::arg("stream"),
            py::arg("LAP"),
            D(classic_packet,check_ac)
        )


        
        .def_static("crcgen",&classic_packet::crcgen,       
            py::arg("payload"),
            py::arg("length"),
            py::arg("UAP"),
            D(classic_packet,crcgen)
        )


        
        .def_static("UAP_from_hec",&classic_packet::UAP_from_hec,       
            py::arg("data"),
            py::arg("hec"),
            D(classic_packet,UAP_from_hec)
        )


        
        .def("crc_check",&classic_packet::crc_check,       
            py::arg("clock"),
            D(classic_packet,crc_check)
        )


        
        .def("decode_header",&classic_packet::decode_header,       
            D(classic_packet,decode_header)
        )


        
        .def("decode_payload",&classic_packet::decode_payload,       
            D(classic_packet,decode_payload)
        )


        
        .def("print",&classic_packet::print,       
            D(classic_packet,print)
        )


        
        .def("tun_format",&classic_packet::tun_format,       
            D(classic_packet,tun_format)
        )


        
        .def("get_LAP",&classic_packet::get_LAP,       
            D(classic_packet,get_LAP)
        )


        
        .def("get_UAP",&classic_packet::get_UAP,       
            D(classic_packet,get_UAP)
        )


        
        .def("set_UAP",&classic_packet::set_UAP,       
            py::arg("UAP"),
            D(classic_packet,set_UAP)
        )


        
        .def("set_NAP",&classic_packet::set_NAP,       
            py::arg("NAP"),
            D(classic_packet,set_NAP)
        )


        
        .def("get_clock",&classic_packet::get_clock,       
            D(classic_packet,get_clock)
        )


        
        .def("set_clock",&classic_packet::set_clock,       
            py::arg("clk6"),
            py::arg("have27"),
            D(classic_packet,set_clock)
        )


        
        .def("try_clock",&classic_packet::try_clock,       
            py::arg("clock"),
            D(classic_packet,try_clock)
        )


        
        .def("header_present",&classic_packet::header_present,       
            D(classic_packet,header_present)
        )


        
        .def("lap_from_fhs",&classic_packet::lap_from_fhs,       
            D(classic_packet,lap_from_fhs)
        )


        
        .def("uap_from_fhs",&classic_packet::uap_from_fhs,       
            D(classic_packet,uap_from_fhs)
        )


        
        .def("nap_from_fhs",&classic_packet::nap_from_fhs,       
            D(classic_packet,nap_from_fhs)
        )


        
        .def("clock_from_fhs",&classic_packet::clock_from_fhs,       
            D(classic_packet,clock_from_fhs)
        )


        
        .def("get_channel",&classic_packet::get_channel,       
            D(classic_packet,get_channel)
        )

        ;


    py::class_<le_packet, gr::bluetooth::packet,
        std::shared_ptr<le_packet>>(m, "le_packet", D(le_packet))

        .def(py::init(&le_packet::make),
           py::arg("stream"),
           py::arg("length"),
           py::arg("freq") = 0.,
           D(le_packet,make)
        )
        




        
        .def_static("freq2chan",&le_packet::freq2chan,       
            py::arg("freq"),
            D(le_packet,freq2chan)
        )


        
        .def_static("chan2index",&le_packet::chan2index,       
            py::arg("chan"),
            D(le_packet,chan2index)
        )


        
        .def_static("freq2index",&le_packet::freq2index,       
            py::arg("freq"),
            D(le_packet,freq2index)
        )


        
        .def_static("sniff_aa",&le_packet::sniff_aa,       
            py::arg("stream"),
            py::arg("stream_length"),
            py::arg("freq"),
            D(le_packet,sniff_aa)
        )


        
        .def("decode_header",&le_packet::decode_header,       
            D(le_packet,decode_header)
        )


        
        .def("decode_payload",&le_packet::decode_payload,       
            D(le_packet,decode_payload)
        )


        
        .def("print",&le_packet::print,       
            D(le_packet,print)
        )


        
        .def("tun_format",&le_packet::tun_format,       
            D(le_packet,tun_format)
        )


        
        .def("header_present",&le_packet::header_present,       
            D(le_packet,header_present)
        )


        
        .def("get_AA",&le_packet::get_AA,       
            D(le_packet,get_AA)
        )


        
        .def("get_channel",&le_packet::get_channel,       
            D(le_packet,get_channel)
        )

        ;




}









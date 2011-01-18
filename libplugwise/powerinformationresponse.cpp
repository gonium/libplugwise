/**
 * This file is part of libplugwise.
 *
 * (c) Fraunhofer ITWM - Mathias Dalheimer <dalheimer@itwm.fhg.de>, 2010
 *
 * libplugwise is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libplugwise is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libplugwise. If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "powerinformationresponse.hpp"
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace plugwise;

std::string PowerInformationResponse::str() {
  std::ostringstream oss;
  oss << "Stick Init Response: " << std::endl;
  oss << "cmd code: " << std::hex << _command_code;
  oss << ", seqno: " << _sequence_number;
  oss << ", ack: " << _acknowledge_code;
  oss << ", chksum: " << _checksum;
  oss << std::endl << "resp_code: " << _response_code;
  oss << ", resp_seq: " << _resp_seq_number;
  oss << ", stick mac: " << _stick_mac_addr;
  oss << ", pulses (1sec interval): " << _pulse_1sec;
  oss << ", pulses (8sec interval): " << _pulse_8sec;
  oss << ", pulses (total): " << _pulse_total;
  return oss.str();
}

void PowerInformationResponse::parse_line2() {
  if (_line2.length() != 56)
    throw plugwise::DataFormatException(
        "Expected 56 chars for response line 2, got " + _line2.length()); 
  _response_code =boost::lexical_cast<uint32_from_hex>(_line2.substr(0,4));
  _resp_seq_number =boost::lexical_cast<uint32_from_hex>(_line2.substr(4,4));
  _stick_mac_addr =(_line2.substr(8,16));
  _pulse_1sec=boost::lexical_cast<uint32_from_hex>(_line2.substr(24,4));
  _pulse_8sec=boost::lexical_cast<uint32_from_hex>(_line2.substr(28,4));
  _pulse_total=boost::lexical_cast<uint32_from_hex>(_line2.substr(32,8));
  // Skipping 3 unknown values, 4 bytes each
  // Skipping also the checksum (for now).
}


bool PowerInformationResponse::req_successful() {
  if (_response_code == 0x0013 ) 
    return true;
  else
    return false;
}


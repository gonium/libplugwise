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


#include "calibrationresponse.hpp"
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace plugwise;

std::string CalibrationResponse::str() {
  std::ostringstream oss;
  oss << "Stick Init Response: " << std::endl;
  oss << "cmd code: " << std::hex << _command_code;
  oss << ", seqno: " << _sequence_number;
  oss << ", ack: " << _acknowledge_code;
  oss << ", chksum: " << _checksum;
  oss << std::endl << "resp_code: " << _response_code;
  oss << ", resp_seq: " << _resp_seq_number;
  oss << ", circle mac: " << _circle_mac_addr;
  oss << ", gain_a: " << _gain_a;
  oss << ", gain_b: " << _gain_b;
  oss << ", off_tot: " << _off_tot;
  oss << ", off_noise: " << _off_noise;
  return oss.str();
}

void CalibrationResponse::parse_line2() {
  //std::cout << "Parsing second response line: " << _line2 << std::endl;
  if (_line2.length() != 60)
    throw plugwise::DataFormatException(
        "Expected 16 chars for response line 2, got " + _line2.length()); 
  _response_code =boost::lexical_cast<uint32_from_hex>(_line2.substr(0,4));
  _resp_seq_number =boost::lexical_cast<uint32_from_hex>(_line2.substr(4,4));
  _circle_mac_addr =(_line2.substr(8,16));
  _gain_a=boost::lexical_cast<float_from_hex>(_line2.substr(24,8));
  _gain_b=boost::lexical_cast<float_from_hex>(_line2.substr(32,8));
  _off_tot=boost::lexical_cast<float_from_hex>(_line2.substr(40,8));
  _off_noise=boost::lexical_cast<float_from_hex>(_line2.substr(48,8));
  // Skipping also the checksum (for now).
}


bool CalibrationResponse::req_successful() {
  if (_response_code == 0x0027) 
    return true;
  else
    return false;
}


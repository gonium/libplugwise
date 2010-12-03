#include "stickinitresponse.hpp"
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace plugwise;

std::string StickInitResponse::str() {
  std::ostringstream oss;
  oss << "Stick Init Response: " << std::endl;
  oss << "cmd code: " << std::hex << _command_code;
  oss << ", seqno: " << _sequence_number;
  oss << ", ack: " << _acknowledge_code;
  oss << ", chksum: " << _checksum;
  oss << std::endl << "resp_code: " << _response_code;
  oss << ", resp_seq: " << _resp_seq_number;
  oss << ", stick mac: " << _stick_mac_addr;
  oss << ", network online: " << _network_online;
  oss << ", network short id: " << _network_short_id;
  return oss.str();
}

void StickInitResponse::parse_line2() {
  //std::cout << "Parsing second response line: " << _line2 << std::endl;
  if (_line2.length() != 54)
    throw plugwise::DataFormatException(
        "Expected 16 chars for response line 2, got " + _line2.length()); 
  _response_code =boost::lexical_cast<uint32_from_hex>(_line2.substr(0,4));
  _resp_seq_number =boost::lexical_cast<uint32_from_hex>(_line2.substr(4,4));
  _stick_mac_addr =(_line2.substr(8,16));
  // Now 2 unknown bytes follow. skipping.
  _network_online=boost::lexical_cast<uint32_from_hex>(_line2.substr(26,2));
  _network_uuid=_line2.substr(28,16);
  _network_short_id=boost::lexical_cast<uint32_from_hex>(_line2.substr(44,4));
  // Now 2 unknown bytes follow. skipping.
  // Skipping also the checksum (for now).
}


#include "stickinitresponse.hpp"
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace plugwise;

std::string StickInitResponse::str() {
  std::ostringstream oss;
  oss << "Stick Init Response: ";
  oss << "cmd code: " << std::hex << command_code;
  oss << ", seqno: " << sequence_number;
  oss << ", ack: " << acknowledge_code;
  oss << ", chksum: " << checksum;
  return oss.str();
}

void StickInitResponse::parse_line2() {
  std::cout << "Parsing second response line: " << _line2 << std::endl;
  if (_line2.length() != 4*4)
    throw plugwise::DataFormatException(
        "Expected 16 chars for response line 2, got " + _line2.length()); 
  //std::cout << "parsing: " << _line2.substr(0,4)  << std::endl;
  command_code =boost::lexical_cast<uint32_from_hex>(_line2.substr(0,4));
  //std::cout << "parsing: " << _line2.substr(4,4)  << std::endl;
  sequence_number =boost::lexical_cast<uint32_from_hex>(_line2.substr(4,4));
  //std::cout << "parsing: " << _line2.substr(8,4)  << std::endl;
  acknowledge_code =boost::lexical_cast<uint32_from_hex>(_line2.substr(8,4));
  //std::cout << "parsing: " << _line2.substr(12,4)  << std::endl;
  checksum =boost::lexical_cast<uint32_from_hex>(_line2.substr(12,4));
}


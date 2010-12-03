#include "response.hpp"
#include <boost/lexical_cast.hpp>


using namespace plugwise;

Response::Response (
    const std::string& line1, 
    const std::string& line2
    ) :
  _line1(line1), _line2(line2) 
{
  parse_line1();
}

bool Response::is_ok() {
  if (_acknowledge_code == 0xc1)
    return true;
  else
    return false;
}

void Response::parse_line1() {
  //std::cout << "Parsing first response line: " << _line1 << std::endl;
  if (_line1.length() != 4*4)
    throw plugwise::DataFormatException(
        "Expected 16 chars for response line 1, got " + _line1.length()); 
  //std::cout << "parsing: " << _line1.substr(0,4)  << std::endl;
  _command_code =boost::lexical_cast<uint32_from_hex>(_line1.substr(0,4));
  //std::cout << "parsing: " << _line1.substr(4,4)  << std::endl;
  _sequence_number =boost::lexical_cast<uint32_from_hex>(_line1.substr(4,4));
  //std::cout << "parsing: " << _line1.substr(8,4)  << std::endl;
  _acknowledge_code =boost::lexical_cast<uint32_from_hex>(_line1.substr(8,4));
  //std::cout << "parsing: " << _line1.substr(12,4)  << std::endl;
  _checksum =boost::lexical_cast<uint32_from_hex>(_line1.substr(12,4));
}

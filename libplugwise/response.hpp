#ifndef LIBPLUGWISE_RESPONSE_HPP
#define LIBPLUGWISE_RESPONSE_HPP 1

#include <common.hpp>
#include <string>
#include <iostream>

namespace plugwise {
  class Response {
    public:
      typedef std::tr1::shared_ptr<Response> Ptr;
      Response () {};
      Response (const std::string& line1, 
                const std::string& line2); 
      virtual std::string str() = 0;
      void parse_line1();
      bool is_ok();
      virtual ~Response() {};

    protected:
      std::string _line1;
      std::string _line2;
      uint32_t _command_code;
      uint32_t _sequence_number;
      uint32_t _acknowledge_code;
      uint32_t _checksum;

    private:
      Response (const Response& original);
      Response& operator= (const Response& rhs);
  };
  // helper for creating numerical variables from strings. See:
  // http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
  class uint32_from_hex   // For use with boost::lexical_cast
  {
    uint32_t value;
    public:
    operator uint32_t() const { return value; }
    friend std::istream& operator>>( std::istream& in, uint32_from_hex& outValue )
    {
      return in >> std::hex >> outValue.value;
    }
  };
};


#endif /* LIBPLUGWISE_RESPONSE_HPP */


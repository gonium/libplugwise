#ifndef LIBPLUGWISE_RESPONSE_HPP
#define LIBPLUGWISE_RESPONSE_HPP 1

#include <common.hpp>

namespace plugwise {
  class Response {
    public:
      typedef std::tr1::shared_ptr<Response> Ptr;
      Response () {};
      virtual std::string str() = 0;
      virtual ~Response() {};

    private:
      Response (const Response& original);
      Response& operator= (const Response& rhs);
      
  };
  
};


#endif /* LIBPLUGWISE_RESPONSE_HPP */


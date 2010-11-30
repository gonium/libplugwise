#ifndef LIBPLUGWISE_REQUEST_HPP
#define LIBPLUGWISE_REQUEST_HPP 1

#include <connection.hpp>
#include <common.hpp>

namespace plugwise {
  class Request {
    public:
      typedef std::tr1::shared_ptr<Request> Ptr;
      Request () {};
      virtual void send(Connection::Ptr con) = 0;
      virtual ~Request() {}; 

    private:
      Request (const Request& original);
      Request& operator= (const Request& rhs);
      
  };
};


#endif /* LIBPLUGWISE_REQUEST_HPP */


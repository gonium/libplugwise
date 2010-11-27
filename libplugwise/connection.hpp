#ifndef LIBPLUGWISE_CONNECTION_HPP
#define LIBPLUGWISE_CONNECTION_HPP 1

#include <string>
#include <iostream>
#include "common.hpp"

namespace plugwise {
  class Connection {
    public:
      typedef std::tr1::shared_ptr<Connection> Ptr;
      Connection (const std::string& device):
        _device(device) {};
      void send();
      virtual ~Connection() {};

    private:
      Connection (const Connection& original);
      Connection& operator= (const Connection& rhs);
      std::string _device;
  };
};


#endif /* LIBPLUGWISE_CONNECTION_HPP */


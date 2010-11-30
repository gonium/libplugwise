/**
 * This file is part of libplugwise.
 *
 * (c) Mathias Dalheimer <md@gonium.net>, 2010
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



#ifndef LIBPLUGWISE_CONNECTION_HPP
#define LIBPLUGWISE_CONNECTION_HPP 1

#include <string>
#include <iostream>
#include "common.hpp"

namespace plugwise {
  class Connection {
    public:
      typedef std::tr1::shared_ptr<Connection> Ptr;
      Connection (const std::string& device);
      void read_response();
      void send_payload(const std::string& payload);
      virtual ~Connection();

    private:
      Connection (const Connection& original);
      Connection& operator= (const Connection& rhs);
      std::string _device;
      int _tty_fd;
  };
};


#endif /* LIBPLUGWISE_CONNECTION_HPP */


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

#ifndef LIBPLUGWISE_STICKINITREQUEST_HPP
#define LIBPLUGWISE_STICKINITREQUEST_HPP 1

#include <request.hpp>
#include <connection.hpp>

namespace plugwise {
  class StickInitRequest : public Request {
    public:
      typedef std::tr1::shared_ptr<StickInitRequest> Ptr;
      StickInitRequest () {};
      void send(plugwise::Connection::Ptr con);
      virtual ~StickInitRequest() {};

    private:
      StickInitRequest (const StickInitRequest& original);
      StickInitRequest& operator= (const StickInitRequest& rhs);
      
  };
  
};


#endif /* LIBPLUGWISE_STICKINITREQUEST_HPP */


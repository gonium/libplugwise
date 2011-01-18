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


#ifndef LIBPLUGWISE_RESPONSEFACTORY_HPP
#define LIBPLUGWISE_RESPONSEFACTORY_HPP 1

#include <common.hpp>
#include <response.hpp>
#include <stickinitresponse.hpp>
#include <powerinformationresponse.hpp>
#include <calibrationresponse.hpp>
#include <connection.hpp>

namespace plugwise {
  class ResponseFactory {
    public:
      typedef std::tr1::shared_ptr<ResponseFactory> Ptr;
      ResponseFactory (Connection::Ptr con) :
        _con(con) {} ;
      Response::Ptr receive();
      StickInitResponse::Ptr receiveStickInitResponse();
      CalibrationResponse::Ptr receiveCalibrationResponse();
      PowerInformationResponse::Ptr receivePowerInformationResponse();
      virtual ~ResponseFactory() {};

    private:
      ResponseFactory (const ResponseFactory& original);
      ResponseFactory& operator= (const ResponseFactory& rhs);
      Connection::Ptr _con;
      
  };
  
};


#endif /* LIBPLUGWISE_RESPONSEFACTORY_HPP */


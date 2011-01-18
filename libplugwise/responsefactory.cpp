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

#include "responsefactory.hpp"
#include <stickinitresponse.hpp>
#include <calibrationresponse.hpp>
#include <powerinformationresponse.hpp>
#include <boost/lexical_cast.hpp>

using namespace plugwise;

Response::Ptr ResponseFactory::receive() {
  std::string line1(_con->read_response());
  std::string line2(_con->read_response());
  // The parsing and evaluation of the response lines is done
  // within the Response class hierarchy. Here, we just 
  // peek into line2 to determine the right response class to
  // redirect to.
  uint32_t response_code=boost::lexical_cast<uint32_from_hex>(line2.substr(0,4));
  switch(response_code) {
    case 0x0011:
      return Response::Ptr(new StickInitResponse(line1, line2));
      break;
    case 0x0027:
      return Response::Ptr(new CalibrationResponse(line1, line2));
      break;
    case 0x0013:
      return Response::Ptr(new PowerInformationResponse(line1, line2));
      break;
  }
  // Just to keep the compiler happy.
  throw CommunicationException("received unknown response.");
}

StickInitResponse::Ptr ResponseFactory::receiveStickInitResponse() {
  std::string line1(_con->read_response());
  std::string line2(_con->read_response());
  uint32_t response_code=boost::lexical_cast<uint32_from_hex>(line2.substr(0,4));
  if (response_code == 0x0011) {
      return StickInitResponse::Ptr(new StickInitResponse(line1, line2));
  } else {
    throw DataFormatException("Expected to parse StickInitResponse");
  }
}

CalibrationResponse::Ptr ResponseFactory::receiveCalibrationResponse() {
  std::string line1(_con->read_response());
  std::string line2(_con->read_response());
  uint32_t response_code=boost::lexical_cast<uint32_from_hex>(line2.substr(0,4));
  if (response_code == 0x0027) {
      return CalibrationResponse::Ptr(new CalibrationResponse(line1, line2));
  } else {
    throw DataFormatException("Expected to parse CalibrationResponse");
  }
}

PowerInformationResponse::Ptr ResponseFactory::receivePowerInformationResponse() {
  std::string line1(_con->read_response());
  std::string line2(_con->read_response());
  uint32_t response_code=boost::lexical_cast<uint32_from_hex>(line2.substr(0,4));
  if (response_code == 0x0013) {
      return PowerInformationResponse::Ptr(new PowerInformationResponse(line1, line2));
  } else {
    throw DataFormatException("Expected to parse PowerInformationResponse");
  }

}

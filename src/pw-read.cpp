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

#include <connection.hpp>
#include <requestfactory.hpp>
#include <responsefactory.hpp>
#include <powerconverter.hpp>
#include <request.hpp>


int main(int argc,char** argv) {

  if (argc != 3) {
    std::cout << "Please start with " << argv[0] << 
      " <stick device> "
      " <circle-id> " << std::endl;
    std::cout << "For example: " << argv[0] 
      << " /dev/ttyUSB0 000D6F00007293BD" << std::endl;
    return -4;
  }

  try {
    plugwise::Connection::Ptr con(new plugwise::Connection(argv[1]));
    plugwise::RequestFactory::Ptr reqFactory(new plugwise::RequestFactory(argv[2]));
    plugwise::ResponseFactory::Ptr respFactory(new plugwise::ResponseFactory(con));

    std::cout << "### Initializing stick" << std::endl;
    plugwise::Request::Ptr si_req=reqFactory->getStickInitRequest();
    si_req->send(con);
    plugwise::Response::Ptr si_resp=respFactory->receive();
    std::cout << "### " << si_resp->str() << std::endl;
    if (si_resp->req_successful())
      std::cout << "initialization successful." << std::endl << std::endl;
    else {
      std::cout << "failed to initialize stick" << std::endl;
      return -1;
    }

    std::cout << "### Sending calibration request " << std::endl;
    plugwise::Request::Ptr ca_req=reqFactory->getCalibrationRequest();
    ca_req->send(con);
    plugwise::CalibrationResponse::Ptr ca_resp=respFactory->receiveCalibrationResponse();
    std::cout << "### " << ca_resp->str() << std::endl;
    if (ca_resp->req_successful())
      std::cout << "calibration successful." << std::endl << std::endl;
    else {
      std::cout << "failed to read calibration values from circle " << std::endl;
      return -2;
    }

    std::cout << "### Sending power information request " << std::endl;
    plugwise::Request::Ptr pi_req=reqFactory->getPowerInformationRequest();
    pi_req->send(con);
    plugwise::PowerInformationResponse::Ptr pi_resp=
      respFactory->receivePowerInformationResponse();
    std::cout << "### " << pi_resp->str() << std::endl;
    if (pi_resp->req_successful())
      std::cout << "initialization successful." << std::endl << std::endl;
    else {
      std::cout << "failed to read calibration values from circle " << std::endl;
      return -3;
    }

    std::cout << "Converting to current power consumption..." << std::endl;
    plugwise::PowerConverter::Ptr pc(new plugwise::PowerConverter(ca_resp));
    double watt=pc->convertToWatt(pi_resp);
    std::cout << "Current power usage: " << watt << " Watt" << std::endl;

  } catch (plugwise::GenericException ge) {
    std::cout << "Aborting: " << ge.what() << std::endl;
  }
}

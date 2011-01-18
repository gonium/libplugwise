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

#include <connection.hpp>
#include <requestfactory.hpp>
#include <responsefactory.hpp>
#include <powerconverter.hpp>
#include <request.hpp>


int main(int argc,char** argv) {

  if (argc < 3) {
    std::cout << "Please start with " << argv[0] << 
      " <stick device> "
      " <circle-id> [<additional-circle-id> <...>]" << std::endl;
    std::cout << "For example: " << argv[0] 
      << " /dev/ttyUSB0 000D6F00007293BD" << std::endl;
    return -4;
  }

  plugwise::Connection::Ptr con(new plugwise::Connection(argv[1]));
  plugwise::RequestFactory::Ptr reqFactory(new plugwise::RequestFactory());
  plugwise::ResponseFactory::Ptr respFactory(new plugwise::ResponseFactory(con));

  try {
    LOG("### Initializing stick");
    plugwise::Request::Ptr si_req=reqFactory->getStickInitRequest();
    si_req->send(con);
    plugwise::Response::Ptr si_resp=respFactory->receive();
    LOG("### " << si_resp->str());
    if (si_resp->req_successful()) {
      LOG("initialization successful.");
    } else {
      std::cout << "failed to initialize stick" << std::endl;
      return -1;
    }
  } catch (plugwise::GenericException ge) {
    std::cout << "Problem while initializing plugwise stick." << std::endl;
    std::cout << "Aborting: " << ge.what() << std::endl;
  }

  // iterate over all circle IDs given on the command line, query and print.
  for (char i=2; i<argc; i++) {
    try {
      LOG("### Sending calibration request ");
      plugwise::Request::Ptr ca_req=reqFactory->getCalibrationRequest(argv[i]);
      ca_req->send(con);
      plugwise::CalibrationResponse::Ptr ca_resp=respFactory->receiveCalibrationResponse();
      LOG("### " << ca_resp->str());
      if (ca_resp->req_successful()) {
        LOG("calibration successful.");
      } else {
        std::cout << "failed to read calibration values from circle " << std::endl;
        return -2;
      }

      LOG("### Sending power information request ");
      plugwise::Request::Ptr pi_req=reqFactory->getPowerInformationRequest(argv[i]);
      pi_req->send(con);
      plugwise::PowerInformationResponse::Ptr pi_resp=
        respFactory->receivePowerInformationResponse();
      LOG("### " << pi_resp->str());
      if (pi_resp->req_successful()) {
        LOG("power info request successful.");
      } else {
        std::cout << "failed to read calibration values from circle " << std::endl;
        return -3;
      }

      LOG("Converting to current power consumption...");
      plugwise::PowerConverter::Ptr pc(new plugwise::PowerConverter(ca_resp));
      double watt=pc->convertToWatt(pi_resp);
      std::cout << argv[i] << ": " << watt << " Watt" << std::endl;
    } catch (plugwise::GenericException ge) {
      std::cout << "Problem while querying circle: " << ge.what() << std::endl;
    }
  }

}

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
#ifndef LIBPLUGWISE_POWERINFORMATIONRESPONSE_HPP
#define LIBPLUGWISE_POWERINFORMATIONRESPONSE_HPP 1


#include <common.hpp>
#include <response.hpp>
#include <string>

namespace plugwise {
  class PowerInformationResponse : public Response {
    public:
      typedef std::tr1::shared_ptr<PowerInformationResponse> Ptr;
      PowerInformationResponse ( const std::string& line1, 
                          const std::string& line2) :
        Response(line1, line2) { parse_line2(); };
      virtual std::string str();
      virtual ~PowerInformationResponse() {};
      bool is_ok();
      uint32_t getPulse1Sec() { return _pulse_1sec; };
      uint32_t getPulse8Sec() { return _pulse_8sec; };
      uint32_t getPulseTotal() { return _pulse_total; };
      virtual bool req_successful();

    private:
      PowerInformationResponse (const PowerInformationResponse& original);
      PowerInformationResponse& operator= (const PowerInformationResponse& rhs);
      void parse_line2();
      uint32_t _response_code;
      uint32_t _resp_seq_number;
      std::string _stick_mac_addr;
      uint32_t _pulse_1sec;
      uint32_t _pulse_8sec;
      uint32_t _pulse_total;
  };
  
};

#endif /* LIBPLUGWISE_POWERINFORMATIONRESPONSE_HPP */

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


#ifndef LIBPLUGWISE_CALIBRATIONRESPONSE_HPP
#define LIBPLUGWISE_CALIBRATIONRESPONSE_HPP 1

#include <common.hpp>
#include <response.hpp>
#include <string>

namespace plugwise {
  class CalibrationResponse : public Response {
    public:
      typedef std::tr1::shared_ptr<CalibrationResponse> Ptr;
      CalibrationResponse ( const std::string& line1, 
                          const std::string& line2) :
        Response(line1, line2) { parse_line2(); };
      virtual std::string str();
      virtual ~CalibrationResponse() {};
      bool is_ok();
      virtual bool req_successful();
      std::string get_circle_mac() { return _circle_mac_addr; };

    private:
      CalibrationResponse (const CalibrationResponse& original);
      CalibrationResponse& operator= (const CalibrationResponse& rhs);
      void parse_line2();
      uint32_t _response_code;
      uint32_t _resp_seq_number;
      std::string _circle_mac_addr;
      float _gain_a;
      float _gain_b;
      float _off_tot;
      float _off_ruis;
  };
  
};

#endif /* LIBPLUGWISE_CALIBRATIONRESPONSE_HPP */

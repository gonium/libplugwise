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

#ifndef LIBPLUGWISE_POWERCONVERTER_HPP
#define LIBPLUGWISE_POWERCONVERTER_HPP 1

#include <calibrationresponse.hpp>
#include <powerinformationresponse.hpp>

namespace plugwise {
  class PowerConverter {
    public:
      typedef std::tr1::shared_ptr<PowerConverter> Ptr;
      PowerConverter (plugwise::CalibrationResponse::Ptr calibration) :
        _calibration(calibration) {};
      double convertToWatt(PowerInformationResponse::Ptr pir);
      virtual ~PowerConverter() {};

    private:
      PowerConverter (const PowerConverter& original);
      PowerConverter& operator= (const PowerConverter& rhs);
      CalibrationResponse::Ptr _calibration;
      
  };
};


#endif /* LIBPLUGWISE_POWERCONVERTER_HPP */


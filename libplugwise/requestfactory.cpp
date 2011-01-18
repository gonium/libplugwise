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

#include "requestfactory.hpp"

using namespace plugwise;

StickInitRequest::Ptr RequestFactory::getStickInitRequest() const {
  return StickInitRequest::Ptr(new StickInitRequest());
}

CalibrationRequest::Ptr RequestFactory::getCalibrationRequest(const std::string& _device_id) const {
  return CalibrationRequest::Ptr(new CalibrationRequest(_device_id));
}

PowerInformationRequest::Ptr RequestFactory::getPowerInformationRequest(const std::string& _device_id) const {
  return PowerInformationRequest::Ptr(new PowerInformationRequest(_device_id));
}

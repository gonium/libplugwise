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

#include "powerconverter.hpp"
#include <common.hpp>
#include <cmath>

using namespace plugwise;

double PowerConverter::convertToWatt(PowerInformationResponse::Ptr pir) {
  // for now, use the second interval data.
  uint32_t pulses = pir->getPulse1Sec();
  if (pulses == 0)
    return 0.0;
  double value = pulses / 1.0;
  double result= 3600 *
    (
      (
        (pow(value + _calibration->get_off_noise(), 2.0) * _calibration->get_gain_b()
        )
        + (value + _calibration->get_off_noise()) * _calibration->get_gain_a()
      )
      + _calibration->get_off_tot()
    );
  //return result;
  return (((result/3600) / 468.9385193) * 1000);
}

// Copyright 2018 ikhatri@umass.edu
// College of Information and Computer Sciences,
// University of Massachusetts Amherst
//
// This software is free: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License Version 3,
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// Version 3 in the file COPYING that came with this distribution.
// If not, see <http://www.gnu.org/licenses/>.
// ========================================================================
#include "config_double.h"

namespace configuration_reader {
namespace config_types {
ConfigDouble::ConfigDouble(std::string key_name) {
  key_ = key_name;
  val_ = 0;
  upper_bound_ = 0;
  lower_bound_ = 0;
  type_ = cdouble;
}

ConfigDouble::ConfigDouble(std::string key_name, double upper_bound,
                           double lower_bound) {
  key_ = key_name;
  val_ = 0;
  upper_bound_ = upper_bound;
  lower_bound_ = lower_bound;
  type_ = cdouble;
}

const double& ConfigDouble::GetVal() {
  const double& d = val_;
  return d;
}

bool ConfigDouble::SetVal(LuaScript* script) {
  double value = script->get<double>(key_);
  if (upper_bound_ != 0 && lower_bound_ != 0) {  // If the bounds exist
    if (value <= lower_bound_ &&
        value >= upper_bound_) {  // Check the value against them
      val_ = value;
      return true;
    } else {
      std::cout << "Value was not between (or equal to) the bounds. Blowing up."
                << std::endl;
      return false;
    }
  } else {  // There are no bounds, set the value
    val_ = value;
    return true;
  }
}
}  // namespace config_types
}  // namespace configuration_reader

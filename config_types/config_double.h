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
#ifndef CONFIGREADER_CONFIGTYPES_CONFIGDOUBLE_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGDOUBLE_H_

#include "config_interface.h"

namespace configuration_reader {
namespace config_types {
class ConfigDouble : public ConfigInterface {
 public:
  ConfigDouble(std::string key_name);
  ConfigDouble(std::string key_name, double upper_bound, double lower_bound);
  const double& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  double upper_bound_;
  double lower_bound_;
  double val_;
};
}  // namespace config_types
}  // namespace configuration_reader
#endif

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
#ifndef CONFIGREADER_CONFIGTYPES_CONFIGFLOAT_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGFLOAT_H_

#include "config_interface.h"

namespace configuration_reader{
namespace config_types{
class ConfigFloat : public ConfigInterface {
 public:
  ConfigFloat(std::string key_name);
  ConfigFloat(std::string key_name, float upper_bound, float lower_bound);
  const float& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  float upper_bound_;
  float lower_bound_;
  float val_;
};
} // namespace config_types
} // namespace configuration_reader
#endif

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
#ifndef CONFIGREADER_CONFIGTYPES_CONFIGINTERFACE_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGINTERFACE_H_

#include <iostream>
#include <string>
#include "../lua_script.h"

namespace configuration_reader {
namespace config_types {

class ConfigInterface {
 public:
  enum ConfigType { cnull, cint, cuint, cdouble, cfloat, cstring, cvector2f };
  std::string GetKey();
  virtual ConfigType GetType();

 protected:
  std::string key_;
  ConfigType type_;
};
}  // namespace config_types
}  // namespace configuration_reader
#endif
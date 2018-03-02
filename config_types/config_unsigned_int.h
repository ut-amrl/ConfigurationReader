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
#ifndef CONFIGREADER_CONFIGTYPES_CONFIGUINT_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGUINT_H_

#include "config_interface.h"

namespace configuration_reader{
namespace config_types{
class ConfigUint : public ConfigInterface {
 public:
  ConfigUint(std::string key_name);
  ConfigUint(std::string key_name, unsigned int upper_bound,
             unsigned int lower_bound);
  const unsigned int& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  unsigned int upper_bound_;
  unsigned int lower_bound_;
  unsigned int val_;
};
} // namespace config_types
} // namespace configuration_reader
#endif

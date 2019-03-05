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
#include "config_string.h"

namespace configuration_reader {
namespace config_types {
ConfigString::ConfigString(std::string key_name) {
  key_ = key_name;
  val_ = "";
  type_= cstring;
}

const std::string& ConfigString::GetVal() {
  const std::string& s = val_;
  return s;
}

bool ConfigString::SetVal(LuaScript* script) {
  val_ = script->get<std::string>(key_);
  return true;
}
}  // namsespace config_types
}  // namespace configuration_reader
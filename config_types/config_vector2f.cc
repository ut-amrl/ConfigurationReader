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
#include "config_vector2f.h"

namespace configuration_reader {
namespace config_types {
ConfigVector2f::ConfigVector2f(std::string key_name) {
  key_ = key_name;
  type_ = ConfigInterface::cvector2f;
}

const Eigen::Vector2f& ConfigVector2f::GetVal() {
  const Eigen::Vector2f& v = val_;
  return v;
}

bool ConfigVector2f::SetVal(LuaScript* script) {
  val_ = script->getVector2f(key_);
  return true;
}
}  // namespace config_types
}  // namespace configuration_reader

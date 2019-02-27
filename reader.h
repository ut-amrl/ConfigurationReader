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

#ifndef READER_H_
#define READER_H_
#include <fstream>
#include <memory>
#include <thread>
#include <unordered_map>
#include "config_double.h"
#include "config_float.h"
#include "config_int.h"
#include "config_interface.h"
#include "config_string.h"
#include "config_unsigned_int.h"
#include "config_vector2f.h"
#include "config_bool.h"

extern "C" {
#include <sys/inotify.h>
#include <unistd.h>
}

namespace configuration_reader {
// Define constants
const std::string kDefaultFileName = "config.lua";

// Define macros for creating new config vars
#define CFG_INT(name, key) const int& CONFIG_##name = InitInt(key)
#define CFG_UINT(name, key) \
  const unsigned int& CONFIG_##name = InitUnsignedInt(key)
#define CFG_DOUBLE(name, key) const double& CONFIG_##name = InitDouble(key)
#define CFG_FLOAT(name, key) const float& CONFIG_##name = InitFloat(key)
#define CFG_STRING(name, key) const std::string& CONFIG_##name = InitString(key)
#define CFG_VECTOR2F(name, key) \
  \
const Eigen::Vector2f& CONFIG_##name = InitVector2f(key)
#define CFG_BOOL(name, key) \
  const bool& CONFIG_##name = configuration_reader::InitBool(key)

void LuaRead(std::vector<std::string> files);
const int& InitInt(std::string key);
const unsigned int& InitUnsignedInt(std::string key);
const double& InitDouble(std::string key);
const float& InitFloat(std::string key);
const std::string& InitString(std::string key);
const Eigen::Vector2f& InitVector2f(std::string key);
void HelpText();
void InitDaemon(std::vector<std::string> files);
void CreateDaemon(std::vector<std::string> files);

extern const Eigen::Vector2f& CONFIG_test;

}  // namespace configuration_reader
#endif

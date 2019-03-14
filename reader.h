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

extern "C" {
#include <sys/epoll.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <libgen.h>
}

#include <atomic>
#include <fstream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>

#include "config_bool.h"
#include "config_double.h"
#include "config_float.h"
#include "config_int.h"
#include "config_interface.h"
#include "config_string.h"
#include "config_unsigned_int.h"
#include "config_vector2d.h"
#include "config_vector2f.h"
#include "config_vector3d.h"

namespace configuration_reader {
// Define constants
const std::string kDefaultFileName = "config.lua";

// Define macros for creating new config vars
#define CONFIG_INT(name, key) const int& CFG_##name = InitInt(key)
#define CONFIG_UINT(name, key) \
  const unsigned int& CFG_##name = InitUnsignedInt(key)
#define CONFIG_DOUBLE(name, key) const double& CFG_##name = InitDouble(key)
#define CONFIG_FLOAT(name, key) const float& CFG_##name = InitFloat(key)
#define CONFIG_STRING(name, key) const std::string& CFG_##name = InitString(key)
#define CONFIG_VECTOR2F(name, key) \
                                   \
  const Eigen::Vector2f& CFG_##name = InitVector2f(key)
#define CONFIG_BOOL(name, key) const bool& CFG_##name = InitBool(key)

#define CONFIG_VECTOR2D(name, key) \
  const Eigen::Vector2d& CFG_##name = InitVector2d(key)
#define CONFIG_VECTOR3D(name, key) \
  const Eigen::Vector3d& CFG_##name = InitVector3d(key)

void LuaRead(std::vector<std::string> files);
const int& InitInt(const std::string& key);
const unsigned int& InitUnsignedInt(const std::string& key);
const double& InitDouble(const std::string& key);
const float& InitFloat(const std::string& key);
const std::string& InitString(const std::string& key);
const bool& InitBool(const std::string& key);
const Eigen::Vector2f& InitVector2f(const std::string& key);
const Eigen::Vector2d& InitVector2d(const std::string& key);
const Eigen::Vector3d& InitVector3d(const std::string& key);
void HelpText();
void InitDaemon(const std::vector<std::string>& files);
void CreateDaemon(const std::vector<std::string>& files);
void Stop();

}  // namespace configuration_reader
#endif

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

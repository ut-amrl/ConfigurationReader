// Copyright 2018 Ishan Khatri
#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <fstream>
#include <memory>
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

using namespace std;

#define DEFAULT_FILENAME "config.lua"
#define MAX_LEN 1024    /*Path length for a directory*/
#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME \
  16 /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE (sizeof(struct inotify_event)) /*size of one event*/
#define BUF_LEN                                                        \
  (MAX_EVENTS * (EVENT_SIZE + LEN_NAME)) /*buffer to store the data of \
                                            events*/

// Define macros for creating new config vars
#define CFG_INT(name, key) const int& CONFIG_##name = ConfigReader::initInt(key)
#define CFG_UINT(name, key) \
  const unsigned int& CONFIG_##name = ConfigReader::initUint(key)
#define CFG_DOUBLE(name, key) \
  const double& CONFIG_##name = ConfigReader::initDouble(key)
#define CFG_FLOAT(name, key) \
  const float& CONFIG_##name = ConfigReader::initFloat(key)
#define CFG_STRING(name, key) \
  const string& CONFIG_##name = ConfigReader::initStr(key)
#define CFG_VECTOR2F(name, key) \
  const Eigen::Vector2f& CONFIG_##name = ConfigReader::initVector2f(key)

class ConfigReader {
 public:
  unordered_map<string, unique_ptr<ConfigInterface>> config;
  ConfigReader(vector<string> f);
  void LuaRead(string filename);
  static void helptext();
  void init();

 protected:
  vector<string> files;
  const int& initInt(string key);
  const unsigned int& initUint(string key);
  const double& initDouble(string key);
  const float& initFloat(string key);
  const string& initStr(string key);
  const Eigen::Vector2f& initVector2f(string key);
};

#endif

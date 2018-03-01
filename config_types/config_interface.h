#ifndef CONFIGREADER_CONFIGTYPES_CONFIGINTERFACE_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGINTERFACE_H_

#include <iostream>
#include <string>
#include "../lua_script.h"

using namespace std;

class ConfigInterface {
 public:
  enum ConfigType { cnull, cint, cuint, cdouble, cfloat, cstring, cvector2f };
  string GetKey();
  virtual ConfigType GetType();

 protected:
  string key_;
  ConfigType type_;
};

#endif
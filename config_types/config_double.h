#ifndef CONFIGREADER_CONFIGTYPES_CONFIGDOUBLE_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGDOUBLE_H_

#include "config_interface.h"

class ConfigDouble : public ConfigInterface {
 public:
  ConfigDouble(string key_name);
  ConfigDouble(string key_name, double upper_bound, double lower_bound);
  const double& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  double upper_bound_;
  double lower_bound_;
  double val_;
};

#endif

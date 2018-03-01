#ifndef CONFIGREADER_CONFIGTYPES_CONFIGFLOAT_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGFLOAT_H_

#include "config_interface.h"

class ConfigFloat : public ConfigInterface {
 public:
  ConfigFloat(string key_name);
  ConfigFloat(string key_name, float upper_bound, float lower_bound);
  const float& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  float upper_bound_;
  float lower_bound_;
  float val_;
};

#endif

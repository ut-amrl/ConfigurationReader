#ifndef CONFIGREADER_CONFIGTYPES_CONFIGFLOAT_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGFLOAT_H_

#include "config_interface.h"

class ConfigFloat : public ConfigInterface {
 public:
  ConfigFloat(string key_name);
  ConfigFloat(string key_name, float upper_bound, float lower_bound);
  const float& getVal();
  bool setVal(LuaScript* script);

 protected:
  float u_bound;
  float l_bound;
  float val;
};

#endif

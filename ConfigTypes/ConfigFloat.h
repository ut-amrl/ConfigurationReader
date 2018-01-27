#ifndef CONFIGFLOAT_H
#define CONFIGFLOAT_H

#include <iostream>
#include "../LuaScript.h"
#include "ConfigInterface.h"

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

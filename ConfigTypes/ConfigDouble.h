#ifndef CONFIGDOUBLE_H
#define CONFIGDOUBLE_H

#include <iostream>
#include "../LuaScript.h"
#include "ConfigInterface.h"

class ConfigDouble : public ConfigInterface {
 public:
  ConfigDouble(string key_name);
  ConfigDouble(string key_name, double upper_bound, double lower_bound);
  const double& getVal();
  bool setVal(LuaScript* script);

 protected:
  double u_bound;
  double l_bound;
  double val;
};

#endif

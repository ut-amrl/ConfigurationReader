#ifndef CONFIGREADER_CONFIGTYPES_CONFIGDOUBLE_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGDOUBLE_H_

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

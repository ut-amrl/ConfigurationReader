#ifndef CONFIGREADER_CONFIGTYPES_CONFIGINT_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGINT_H_

#include "config_interface.h"

class ConfigInt : public ConfigInterface {
 public:
  ConfigInt(string key_name);
  ConfigInt(string key_name, int upper_bound, int lower_bound);
  int& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  int upper_bound_;
  int lower_bound_;
  int val_;
};

#endif

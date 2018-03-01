#ifndef CONFIGREADER_CONFIGTYPES_CONFIGUINT_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGUINT_H_

#include "config_interface.h"

class ConfigUint : public ConfigInterface {
 public:
  ConfigUint(string key_name);
  ConfigUint(string key_name, unsigned int upper_bound,
             unsigned int lower_bound);
  const unsigned int& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  unsigned int upper_bound_;
  unsigned int lower_bound_;
  unsigned int val_;
};

#endif

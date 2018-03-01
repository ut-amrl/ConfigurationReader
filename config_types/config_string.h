#ifndef CONFIGREADER_CONFIGTYPES_CONFIGSTRING_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGSTRING_H_

#include "config_interface.h"

class ConfigString : public ConfigInterface {
 public:
  ConfigString(string key_name);
  const string& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  string val_;
};

#endif
#ifndef CONFIGREADER_CONFIGTYPES_CONFIGSTRING_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGSTRING_H_

#include "ConfigInterface.h"

class ConfigString : public ConfigInterface {
 public:
  ConfigString(string key_name);
  const string& getVal();
  bool setVal(LuaScript* script);

 protected:
  string val;
};

#endif
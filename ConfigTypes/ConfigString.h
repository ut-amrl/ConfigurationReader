#ifndef CONFIGSTRING_H
#define CONFIGSTRING_H

#include <iostream>
#include "../LuaScript.h"
#include "ConfigInterface.h"

class ConfigString : public ConfigInterface {
 public:
  ConfigString(string key_name);
  string getVal();
  bool setVal(LuaScript* script);

 protected:
  string val;
};

#endif
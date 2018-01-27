#include "ConfigString.h"

ConfigString::ConfigString(string key_name) {
  key = key_name;
  val = "";
  type = ConfigInterface::cstring;
}

const string& ConfigString::getVal() { 
  const string& s = val;
  return s; 
}

bool ConfigString::setVal(LuaScript* script) {
  val = script->get<string>(key);
  return true;
}
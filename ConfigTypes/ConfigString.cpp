#include "ConfigString.h"

ConfigString::ConfigString(string key_name) {
  key = key_name;
  val = "";
  type = ConfigInterface::cstring;
}

string ConfigString::getVal() { return val; }

bool ConfigString::setVal(LuaScript* script) {
  val = script->get<string>(key);
  return true;
}
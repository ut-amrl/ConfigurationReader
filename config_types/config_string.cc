#include "config_string.h"

ConfigString::ConfigString(string key_name) {
  key_ = key_name;
  val_ = "";
  type_ = ConfigInterface::cstring;
}

const string& ConfigString::GetVal() {
  const string& s = val_;
  return s;
}

bool ConfigString::SetVal(LuaScript* script) {
  val_ = script->get<string>(key_);
  return true;
}
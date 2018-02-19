#include "ConfigVector2f.h"

ConfigVector2f::ConfigVector2f(string key_name) {
  key = key_name;
  //val = "";
  type = ConfigInterface::cvector2f;
}

const Eigen::Vector2f& ConfigVector2f::getVal() { 
  const Eigen::Vector2f& v = val;
  return v; 
}

bool ConfigVector2f::setVal(LuaScript* script) {
  val = script->getVector2f(key);
  return true;
}
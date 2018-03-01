#include "config_vector2f.h"

ConfigVector2f::ConfigVector2f(string key_name) {
  key_ = key_name;
  type_ = ConfigInterface::cvector2f;
}

const Eigen::Vector2f& ConfigVector2f::GetVal() {
  const Eigen::Vector2f& v = val_;
  return v;
}

bool ConfigVector2f::SetVal(LuaScript* script) {
  val_ = script->getVector2f(key_);
  return true;
}
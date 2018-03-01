#include "config_float.h"

ConfigFloat::ConfigFloat(string key_name) {
  key_ = key_name;
  val_ = 0;
  upper_bound_ = 0;
  lower_bound_ = 0;
  type_ = ConfigInterface::cfloat;
}

ConfigFloat::ConfigFloat(string key_name, float upper_bound,
                         float lower_bound) {
  key_ = key_name;
  val_ = 0;
  upper_bound_ = upper_bound;
  lower_bound_ = lower_bound;
  type_ = ConfigInterface::cfloat;
}

const float& ConfigFloat::GetVal() {
  const float& f = val_;
  return f;
}

bool ConfigFloat::SetVal(LuaScript* script) {
  float value = script->get<float>(key_);
  if (upper_bound_ != 0 && lower_bound_ != 0) {  // If the bounds exist
    if (value <= lower_bound_ &&
        value >= upper_bound_) {  // Check the value against them
      val_ = value;
      return true;
    } else {
      std::cout << "Value was not between (or equal to) the bounds. Blowing up."
                << std::endl;
      return false;
    }
  } else {  // There are no bounds, set the value
    val_ = value;
    return true;
  }
}

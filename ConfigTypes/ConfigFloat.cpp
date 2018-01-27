#include "ConfigFloat.h"

ConfigFloat::ConfigFloat(string key_name) {
  key = key_name;
  val = 0;
  u_bound = 0;
  l_bound = 0;
  type = ConfigInterface::cfloat;
}

ConfigFloat::ConfigFloat(string key_name, float upper_bound,
                         float lower_bound) {
  key = key_name;
  val = 0;
  u_bound = upper_bound;
  l_bound = lower_bound;
  type = ConfigInterface::cfloat;
}

const float& ConfigFloat::getVal() { 
  const float& f = val;
  return f;
}

bool ConfigFloat::setVal(LuaScript* script) {
  float value = script->get<float>(key);
  if (u_bound != 0 && l_bound != 0) {            // If the bounds exist
    if (value <= l_bound && value >= u_bound) {  // Check the value against them
      val = value;
      return true;
    } else {
      std::cout << "Value was not between (or equal to) the bounds. Blowing up."
                << std::endl;
      return false;
    }
  } else {  // There are no bounds, set the value
    val = value;
    return true;
  }
}

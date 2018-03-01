#include "ConfigUint.h"

ConfigUint::ConfigUint(string key_name) {
  key = key_name;
  val = 0;
  u_bound = 0;
  l_bound = 0;
  type = ConfigInterface::cuint;
}

ConfigUint::ConfigUint(string key_name, unsigned int upper_bound,
                       unsigned int lower_bound) {
  key = key_name;
  val = 0;
  u_bound = upper_bound;
  l_bound = lower_bound;
  type = ConfigInterface::cuint;
}

const unsigned int& ConfigUint::getVal() {
  const unsigned int& u = val;
  return u;
}

bool ConfigUint::setVal(LuaScript* script) {
  unsigned int value = script->get<unsigned int>(key);
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

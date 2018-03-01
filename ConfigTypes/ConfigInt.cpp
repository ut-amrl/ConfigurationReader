#include "ConfigInt.h"

ConfigInt::ConfigInt(string key_name) {
  key = key_name;
  val = 0;
  u_bound = 0;
  l_bound = 0;
  type = ConfigInterface::cint;
}

ConfigInt::ConfigInt(string key_name, int upper_bound, int lower_bound) {
  key = key_name;
  val = 0;
  u_bound = upper_bound;
  l_bound = lower_bound;
  type = ConfigInterface::cint;
}

int& ConfigInt::getVal() {
  int& i = val;
  return i;
}

bool ConfigInt::setVal(LuaScript* script) {
  int value = script->get<int>(key);
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

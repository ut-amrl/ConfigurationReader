#include "ConfigDouble.h"

ConfigDouble::ConfigDouble(string key_name) {
  key = key_name;
  val = 0;
  u_bound = 0;
  l_bound = 0;
  type = ConfigInterface::cdouble;
}

ConfigDouble::ConfigDouble(string key_name, double upper_bound,
                           double lower_bound) {
  key = key_name;
  val = 0;
  u_bound = upper_bound;
  l_bound = lower_bound;
  type = ConfigInterface::cdouble;
}

const double& ConfigDouble::getVal() { 
  const double& d = val;
  return d;
}

bool ConfigDouble::setVal(LuaScript* script) {
  double value = script->get<double>(key);
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

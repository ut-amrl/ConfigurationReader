#include "config_unsigned_int.h"

ConfigUint::ConfigUint(string key_name) {
  key_ = key_name;
  val_ = 0;
  upper_bound_ = 0;
  lower_bound_ = 0;
  type_ = ConfigInterface::cuint;
}

ConfigUint::ConfigUint(string key_name, unsigned int upper_bound,
                       unsigned int lower_bound) {
  key_ = key_name;
  val_ = 0;
  upper_bound_ = upper_bound;
  lower_bound_ = lower_bound;
  type_ = ConfigInterface::cuint;
}

const unsigned int& ConfigUint::GetVal() {
  const unsigned int& u = val_;
  return u;
}

bool ConfigUint::SetVal(LuaScript* script) {
  unsigned int value = script->get<unsigned int>(key_);
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

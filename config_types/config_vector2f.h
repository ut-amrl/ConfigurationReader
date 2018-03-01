#ifndef CONFIGREADER_CONFIGTYPES_CONFIGVECTOR2F_H_
#define CONFIGREADER_CONFIGTYPES_CONFIGVECTOR2F_H_

#include "config_interface.h"

class ConfigVector2f : public ConfigInterface {
 public:
  ConfigVector2f(string key_name);
  const Eigen::Vector2f& GetVal();
  bool SetVal(LuaScript* script);

 protected:
  Eigen::Vector2f val_;
};

#endif
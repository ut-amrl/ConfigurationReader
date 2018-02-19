#ifndef CONFIGVECTOR2F_H
#define CONFIGVECTOR2F_H

#include <iostream>
#include "../LuaScript.h"
#include "ConfigInterface.h"

class ConfigVector2f : public ConfigInterface {
 public:
  ConfigVector2f(string key_name);
  const Eigen::Vector2f& getVal();
  bool setVal(LuaScript* script);

 protected:
  Eigen::Vector2f val;
};

#endif
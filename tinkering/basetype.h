#pragma once

#include "configtype.h"
#include "lua_script.h"

namespace types {
class BaseType {
 protected:
  std::string key_;

 public:
  BaseType() = delete;
  BaseType(const std::string& key) : key_(key) {}
  virtual ~BaseType() = default;
  virtual ConfigType GetType() const = 0;
  virtual void SetVal(lua_reading::LuaScript* script) = 0;
};
}  // namespace types

#pragma once

#include "basetype.h"
#include "configtype.h"
#include "lua_script.h"

namespace types {
class IntType : public BaseType {
 private:
  int val_;

 public:
  IntType() = delete;
  IntType(const std::string& key) : BaseType(key), val_(0) {}
  ~IntType() = default;
  ConfigType GetType() const override { return ConfigType::CINT; }

  const int& GetVal() { return val_; }
  void SetVal(const int& i) { val_ = i; }
  void SetVal(lua_reading::LuaScript* script) override {
    val_ = script->get<int>(key_);
  }
};
}  // namespace types

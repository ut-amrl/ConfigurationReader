#pragma once

#include "configtype.h"

namespace types {
class BaseType {
 public:
  BaseType() = default;
  virtual ~BaseType() = default;
  virtual ConfigType GetType();
};
}  // namespace types

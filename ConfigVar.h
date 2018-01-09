// Copyright 2017 Ishan Khatri
#ifndef CONFIGVAR_H
#define CONFIGVAR_H
#include <string>
#include "ConfigInterface.h"

using namespace std;
template <class T>

class ConfigVar : public ConfigInterface {
 public:
  ConfigVar(string key_name, string subtree_name);

  // Using void* here is kind of gross but also unavoidable...
  void* getVal();
  void setVal(void* value);

 protected:
  T* val;
};

#endif

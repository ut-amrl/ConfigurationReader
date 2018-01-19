#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H
#include <string>

using namespace std;

class ConfigInterface {
 public:
  enum ConfigType { cnull, cint, cuint, cdouble, cfloat, cstring, cvector2f };
  // ConfigInterface(string key_name, string subtree_name);
  string getKey();
  // virtual void* getVal();
  // virtual void setVal(void* value);
  virtual ConfigType getType();

 protected:
  string key;
  ConfigType type;
};

#endif
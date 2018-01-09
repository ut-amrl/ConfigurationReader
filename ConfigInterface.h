#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H
#include <string>

using namespace std;

class ConfigInterface {
 public:
  // ConfigInterface(string key_name, string subtree_name);
  string getKey();
  string getSubtree();
  virtual void* getVal();
  virtual void setVal(void* value);

 protected:
  string key;
  string subtree;
};

#endif
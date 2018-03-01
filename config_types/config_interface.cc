#include "config_interface.h"

using namespace std;

/*ConfigInterface::ConfigInterface(string key_name, string subtree_name) {
  key_ = key_name;
  subtree = subtree_name;
}*/
string ConfigInterface::GetKey() { return key_; }
// string ConfigInterface::getSubtree() { return subtree; }
ConfigInterface::ConfigType ConfigInterface::GetType() { return type_; }
// void* ConfigInterface::GetVal() { return NULL; }
// void ConfigInterface::SetVal(void* value) { return; }
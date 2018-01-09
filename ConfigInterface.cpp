#include "ConfigInterface.h"

using namespace std;

/*ConfigInterface::ConfigInterface(string key_name, string subtree_name) {
  key = key_name;
  subtree = subtree_name;
}*/
string ConfigInterface::getKey() { return key; }
string ConfigInterface::getSubtree() { return subtree; }
void* ConfigInterface::getVal() { return NULL; }
void ConfigInterface::setVal(void* value) { return; }
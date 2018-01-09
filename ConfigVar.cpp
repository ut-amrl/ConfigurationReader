#include "ConfigVar.h"

using namespace std;

template <class T>
ConfigVar<T>::ConfigVar(string key_name, string subtree_name) {
  key = key_name;
  subtree = subtree_name;
}

template <class T>
void* ConfigVar<T>::getVal() {
  return val;
}

template <class T>
void ConfigVar<T>::setVal(void* value) {
  val = (T*)value;
  return;
}
// Copyright 2018 Ishan Khatri
#include <fstream>
#include <memory>
#include <unordered_map>
#include "ConfigDouble.h"
#include "ConfigFloat.h"
#include "ConfigInt.h"
#include "ConfigInterface.h"
#include "ConfigString.h"
#include "ConfigUint.h"

extern "C" {
#include <sys/inotify.h>
#include <unistd.h>
}

// Define constants
#define FOLDER_PATH \
  "/home/ishan/Share/ConfigurationReader/"  // Must be specified so that we can
                                            // watch the directory for changes
#define DEFAULT_FILENAME "config.lua"
#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

using namespace std;

unordered_map<string, unique_ptr<ConfigInterface>> config;

// Macros for expanding strings
#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

// Define macros for creating new config vars
#define CFG_INT(key) \
  const int& CONFIG_##key = initInt(STR_EXPAND(key))
#define CFG_UINT(key) \
  const unsigned int& CONFIG_##key = initUint(STR_EXPAND(key))
#define CFG_DOUBLE(key) \
  const double& CONFIG_##key = initDouble(STR_EXPAND(key))
#define CFG_FLOAT(key) \
  const float& CONFIG_##key = initFloat(STR_EXPAND(key))
#define CFG_STRING(key) \
  const string& CONFIG_##key = initStr(STR_EXPAND(key))

/*
  The read() function takes in a filename as a parameter
  and updates all the config values from the unordered map
*/
void read(string filename) {
  // Create the LuaScript object
  LuaScript script(filename);
  // Loop through the unordered map
  unordered_map<string, unique_ptr<ConfigInterface>>::iterator itr;
  for (itr = config.begin(); itr != config.end(); itr++) {
    // Create a temporary pointer because you can't static_cast a unique_ptr
    ConfigInterface* t = itr->second.get();
    // Switch statement that serves as a runtime typecheck
    // See the ConfigInterface.h file for documentation on the ConfigType enum &
    // the getType() function
    switch (itr->second->getType()) {
      case (1):  // int
      {
        ConfigInt* temp = static_cast<ConfigInt*>(t);
        temp->setVal(&script);
        cout << temp->getKey() << " (int) was set to " << temp->getVal()
             << endl;
        break;
      }
      case (2):  // uint
      {
        ConfigUint* temp = static_cast<ConfigUint*>(t);
        temp->setVal(&script);
        cout << temp->getKey() << " (uint) was set to " << temp->getVal()
             << endl;
        break;
      }
      case (3):  // double
      {
        ConfigDouble* temp = static_cast<ConfigDouble*>(t);
        temp->setVal(&script);
        cout << temp->getKey() << " (double) was set to " << temp->getVal()
             << endl;
        break;
      }
      case (4):  // float
      {
        ConfigFloat* temp = static_cast<ConfigFloat*>(t);
        temp->setVal(&script);
        cout << temp->getKey() << " (float) was set to " << temp->getVal()
             << endl;
        break;
      }
      case (5):  // string
      {
        ConfigString* temp = static_cast<ConfigString*>(t);
        temp->setVal(&script);
        cout << temp->getKey() << " (string) was set to " << temp->getVal()
             << endl;
        break;
      }
      case (6):  // vector2f
      {
        cout << "Implementation TBD" << endl;
        break;
      }
      case (0):  // null type: the type value used when a ConfigInterface is
                 // constructed -> should never actually be used
        cout << "This should never happen" << endl;
        break;
    }
  }
}

const int& initInt(string key) {
  config[key] = unique_ptr<ConfigInterface>(new ConfigInt(key));
  ConfigInterface* t = config.find(key)->second.get();
  ConfigInt* temp = static_cast<ConfigInt*>(t);
  return temp->getVal();
}

const unsigned int& initUint(string key) {
  config[key] = unique_ptr<ConfigInterface>(new ConfigUint(key));
  ConfigInterface* t = config.find(key)->second.get();
  ConfigUint* temp = static_cast<ConfigUint*>(t);
  return temp->getVal();
}

const double& initDouble(string key) {
  config[key] = unique_ptr<ConfigInterface>(new ConfigDouble(key));
  ConfigInterface* t = config.find(key)->second.get();
  ConfigDouble* temp = static_cast<ConfigDouble*>(t);
  return temp->getVal();
}

const float& initFloat(string key) {
  config[key] = unique_ptr<ConfigInterface>(new ConfigFloat(key));
  ConfigInterface* t = config.find(key)->second.get();
  ConfigFloat* temp = static_cast<ConfigFloat*>(t);
  return temp->getVal();
}

const string& initStr(string key) {
  config[key] = unique_ptr<ConfigInterface>(new ConfigString(key));
  ConfigInterface* t = config.find(key)->second.get();
  ConfigString* temp = static_cast<ConfigString*>(t);
  return temp->getVal();
}

void helptext() {
  cout << "Please pass in zero or one lua files as an "
          "argument to the program."
       << endl;
  cout << "If you do not pass in a file, the program will use the "
          "default filename which is currently set to: "
       << DEFAULT_FILENAME << endl;
  cout << "Usage: ./reader filename.lua" << endl;
}

int main(int argc, char* argv[]) {
  int length, wd, fd, i = 0;
  char buffer[EVENT_BUF_LEN];

  /*creating the INOTIFY instance*/
  fd = inotify_init();

  /*checking for error*/
  if (fd < 0) {
    cout << "inotify error" << endl;
  }

  string filePath = FOLDER_PATH;
  string filename = "";

  if (argc > 2) {
    cout << "Incorrect usage. ";
    helptext();
  } else if (argc == 2) {
    string t = argv[1];
    if (t == "-h" || t == "-help" || t == "--help") {
      helptext();
      return 0;
    }
    filePath += argv[1];
    filename += argv[1];
    read(filename);
  } else {
    filePath += DEFAULT_FILENAME;
    filename = DEFAULT_FILENAME;
    read(filename);
  }

  wd = inotify_add_watch(fd, filePath.c_str(), IN_MODIFY);

  length = read(fd, buffer, EVENT_BUF_LEN);

  if (length < 0) {
    cout << "inotify error" << endl;
  }

  while (i < length) {
    struct inotify_event* event = (struct inotify_event*)&buffer[i];
    if (event->mask & IN_MODIFY) {
      cout << filename << " has been modified" << endl;
      read(filename);
    }
    i += EVENT_SIZE + event->len;
  }

  inotify_rm_watch(fd, wd);
  close(fd);
}

// Copyright 2017 Ishan Khatri
#include <fstream>
#include "ConfigInterface.h"
#include "ConfigVar.cpp"
#include "ConfigVar.h"
#include "LuaScript.h"

extern "C" {
#include <sys/inotify.h>
#include <unistd.h>
}

// Define constants
#define DEFAULT_FILENAME "config.lua"
#define NUM_CONFIG_VARS 1
#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

using namespace std;

vector<ConfigInterface*> flags;

// Define macros for creating new config vars
#define NEW_INT(key, subtree) \
  flags.emplace_back(new ConfigVar<int>(key, subtree));
#define NEW_UINT(key, subtree) \
  flags.emplace_back(new ConfigVar<unsigned int>(key, subtree));
#define NEW_DOUBLE(key, subtree) \
  flags.emplace_back(new ConfigVar<double>(key, subtree));
#define NEW_FLOAT(key, subtree) \
  flags.emplace_back(new ConfigVar<float>(key, subtree));
#define NEW_STRING(key, subtree) \
  flags.emplace_back(new ConfigVar<string>(key, subtree));

void read(string filename) {
  LuaScript script(filename);
  for (int x = 0; x < flags.size(); x++) {
    string tname = (flags[x]->getSubtree() == "")
                       ? flags[x]->getKey()
                       : flags[x]->getKey() + "." + flags[x]->getSubtree();
    string t = script.get<string>(tname);
    flags[x]->setVal(&t);
    string* p = (string*)flags[x]->getVal();
    cout << flags[x]->getKey() << " was loaded with a value of " << *p << endl;
  }
}

void init() {
  // NEW_INT("number", "");
  NEW_STRING("testString", "");
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

  string filePath = "/home/ishan/Share/ConfigurationReader/";
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
    init();
    filePath += argv[1];
    filename += argv[1];
    read(filename);
  } else {
    init();
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

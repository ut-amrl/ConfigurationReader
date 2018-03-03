// Copyright 2018 ikhatri@umass.edu
// College of Information and Computer Sciences,
// University of Massachusetts Amherst
//
// This software is free: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License Version 3,
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// Version 3 in the file COPYING that came with this distribution.
// If not, see <http://www.gnu.org/licenses/>.
// ========================================================================
#include "reader.h"

namespace configuration_reader {
// Define constants
//#define FOLDER_PATH \
  "/home/ishan/Share/ConfigurationReader/"  // Must be specified so that we can
                                            // watch the directory for changess
#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

namespace {
std::unordered_map<std::string, std::unique_ptr<config_types::ConfigInterface>>
    config;
}  // namespace

/*
  The LuaRead() function takes in a filename as a parameter
  and updates all the config values from the unordered map
*/
//void LuaRead(std::string filename) {
void LuaRead(std::vector<std::string> files){
  // Create the LuaScript object
  LuaScript script(files);
  // Loop through the unordered map
  std::unordered_map<std::string,
                     std::unique_ptr<config_types::ConfigInterface>>::iterator
      itr;
  for (itr = config.begin(); itr != config.end(); itr++) {
    // Create a temporary pointer because you can't static_cast a unique_ptr
    config_types::ConfigInterface* t = itr->second.get();
    // Switch statement that serves as a runtime typecheck
    // See the ConfigInterface.h file for documentation on the ConfigType enum &
    // the GetType() function
    switch (itr->second->GetType()) {
      case (1):  // int
      {
        config_types::ConfigInt* temp =
            static_cast<config_types::ConfigInt*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (int) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (2):  // uint
      {
        config_types::ConfigUint* temp =
            static_cast<config_types::ConfigUint*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (uint) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (3):  // double
      {
        config_types::ConfigDouble* temp =
            static_cast<config_types::ConfigDouble*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (double) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (4):  // float
      {
        config_types::ConfigFloat* temp =
            static_cast<config_types::ConfigFloat*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (float) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (5):  // string
      {
        config_types::ConfigString* temp =
            static_cast<config_types::ConfigString*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (string) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (6):  // vector2f
      {
        config_types::ConfigVector2f* temp =
            static_cast<config_types::ConfigVector2f*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (Vector2f) was set to "
                  << temp->GetVal() << std::endl;
        break;
      }
      case (0):  // null type: the type value used when a ConfigInterface is
                 // constructed -> should never actually be used
        std::cout << "This should never happen" << std::endl;
        break;
    }
  }
}

const int& InitInt(std::string key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigInt(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigInt* temp = static_cast<config_types::ConfigInt*>(t);
  return temp->GetVal();
}

const unsigned int& InitUnsignedInt(std::string key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigUint(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigUint* temp = static_cast<config_types::ConfigUint*>(t);
  return temp->GetVal();
}

const double& InitDouble(std::string key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigDouble(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigDouble* temp =
      static_cast<config_types::ConfigDouble*>(t);
  return temp->GetVal();
}

const float& InitFloat(std::string key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigFloat(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigFloat* temp = static_cast<config_types::ConfigFloat*>(t);
  return temp->GetVal();
}

const std::string& InitString(std::string key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigString(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigString* temp =
      static_cast<config_types::ConfigString*>(t);
  return temp->GetVal();
}

const Eigen::Vector2f& InitVector2f(std::string key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigVector2f(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigVector2f* temp =
      static_cast<config_types::ConfigVector2f*>(t);
  return temp->GetVal();
}

void HelpText() {
  std::cout << "Please pass in zero or more lua files as an "
               "argument to the program."
            << std::endl;
  std::cout << "If you do not pass in a file, the program will use the "
               "default filename which is currently set to: "
            << kDefaultFileName << std::endl;
  std::cout << "Usage: ./reader filename.lua" << std::endl;
}

void InitDaemon(std::vector<std::string> files) {
  int length, wd, fd, i = 0;
  char buffer[EVENT_BUF_LEN];

  // Initialize inotify
  fd = inotify_init();
  if (fd < 0) {
    std::cout << "ERROR: Couldn't initialize inotify" << std::endl;
  }

  // Load in the files for the first time
  LuaRead(files);

  // Add all the files to be watched
  for (std::string f : files) {
    //LuaRead(f);
    wd = inotify_add_watch(fd, f.c_str(), IN_MODIFY);
    if (wd == -1)
      std::cout << "ERROR: Couldn't add watch to the file: " << f << std::endl;
  }

  // Loop forever, checking for changes to the files above
  while (1) {
    i = 0;
    length = read(fd, buffer, EVENT_BUF_LEN);
    if (length < 0) std::cout << "ERROR: Inotify read failed" << std::endl;

    while (i < length) {
      struct inotify_event* event = (struct inotify_event*)&buffer[i];
      if (event->mask & IN_MODIFY) {  // If the event was a modify event
        LuaRead(files); // Reload all the files
      }
      i += EVENT_SIZE + event->len;
    }
  }
  // Clean up
  inotify_rm_watch(fd, wd);
  close(fd);
}

void CreateDaemon(std::vector<std::string> files){
  std::thread daemon(InitDaemon, files);
  if(daemon.joinable())
    daemon.detach();
}

CFG_VECTOR2F(test, "tree.testVec");
CFG_INT(someInt, "testInt2");

}  // namespace Configuration Reader

// int main(int argc, char* argv[]) {
//   int length, wd, fd, i = 0;
//   char buffer[EVENT_BUF_LEN];

//   /*creating the INOTIFY instance*/
//   fd = inotify_init();

//   /*checking for error*/
//   if (fd < 0) {
//     std::cout << "inotify error" << std::endl;
//   }

//   std::string filePath = FOLDER_PATH;
//   std::string filename = "";

//   if (argc > 2) {
//     std::cout << "Incorrect usage. ";
//     configuration_reader::HelpText();
//   } else if (argc == 2) {
//     std::string t = argv[1];
//     if (t == "-h" || t == "-help" || t == "--help") {
//       configuration_reader::HelpText();
//       return 0;
//     }
//     filePath += argv[1];
//     filename += argv[1];
//     configuration_reader::LuaRead(filename);
//   } else {
//     filePath += DEFAULT_FILENAME;
//     filename = DEFAULT_FILENAME;
//     configuration_reader::LuaRead(filename);
//   }

//   wd = inotify_add_watch(fd, filePath.c_str(), IN_MODIFY);

//   // Loop forever, checking for changes to the files above
//   while (1) {
//     i = 0;
//     length = read(fd, buffer, EVENT_BUF_LEN);
//     if (length < 0) std::cout << "ERROR: Inotify read failed" << std::endl;

//     while (i < length) {
//       struct inotify_event* event = (struct inotify_event*)&buffer[i];
//       if (event->mask & IN_MODIFY) {  // If the event was a modify event
//         std::cout << filename << " has been modified" << std::endl;
//         configuration_reader::LuaRead(filename);
//         std::cout << "New value: " << configuration_reader::CONFIG_test
//                   << std::endl;
//       }
//       i += EVENT_SIZE + event->len;
//     }
//   }
//   inotify_rm_watch(fd, wd);
//   close(fd);
// }

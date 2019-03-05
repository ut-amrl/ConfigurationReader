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
#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

static constexpr int kInotifySleep = 50;

// Atomic bool for the thread
std::atomic_bool is_running_;
std::thread daemon_;

namespace {
std::unordered_map<std::string, std::unique_ptr<config_types::ConfigInterface>>
    config;
}  // namespace

/*
  The LuaRead() function takes in a filename as a parameter
  and updates all the config values from the unordered map
*/
// void LuaRead(std::string filename) {
void LuaRead(std::vector<std::string> files) {
  // Create the LuaScript object
  LuaScript script(files);
  // Loop through the unordered map
  for (const auto& pair : config) {
    // Create a temporary pointer because you can't static_cast a unique_ptr
    config_types::ConfigInterface* t = pair.second.get();
    // Switch statement that serves as a runtime typecheck
    // See the ConfigInterface.h file for documentation on the ConfigType enum
    // and the GetType() function
    switch (pair.second->GetType()) {
      case (config_types::cint):
      {
        config_types::ConfigInt* temp =
            static_cast<config_types::ConfigInt*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (int) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (config_types::cuint):
      {
        config_types::ConfigUint* temp =
            static_cast<config_types::ConfigUint*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (uint) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (config_types::cdouble):
      {
        config_types::ConfigDouble* temp =
            static_cast<config_types::ConfigDouble*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (double) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (config_types::cfloat):
      {
        config_types::ConfigFloat* temp =
            static_cast<config_types::ConfigFloat*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (float) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (config_types::cstring):
      {
        config_types::ConfigString* temp =
            static_cast<config_types::ConfigString*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (string) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      case (config_types::cvector2f):
      {
        config_types::ConfigVector2f* temp =
            static_cast<config_types::ConfigVector2f*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (Vector2f) was set to "
                  << temp->GetVal() << std::endl;
        break;
      }
      case (config_types::cbool):
      {
        config_types::ConfigBool* temp =
            static_cast<config_types::ConfigBool*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (boolean) was set to "
                  << temp->GetVal() << std::endl;
        break;
      }
      case (config_types::cvector2d):
      {
        config_types::ConfigVector2d* temp =
            static_cast<config_types::ConfigVector2d*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (Vector2d) was set to "
                  << temp->GetVal() << std::endl;
        break;
      }
      case (config_types::cvector3d):
      {
        config_types::ConfigVector3d* temp =
            static_cast<config_types::ConfigVector3d*>(t);
        temp->SetVal(&script);
        std::cout << temp->GetKey() << " (Vector3d) was set to "
                  << temp->GetVal() << std::endl;
        break;
      }
      default:  // null type: the type value used when a ConfigInterface is
                 // constructed -> should never actually be used
        std::cerr << "ERROR: ConfigType enum has a value of null, this should never happen!" << std::endl;
        break;
    }
  }
}

const int& InitInt(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigInt(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigInt* temp = static_cast<config_types::ConfigInt*>(t);
  return temp->GetVal();
}

const unsigned int& InitUnsignedInt(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigUint(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigUint* temp = static_cast<config_types::ConfigUint*>(t);
  return temp->GetVal();
}

const double& InitDouble(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigDouble(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigDouble* temp =
      static_cast<config_types::ConfigDouble*>(t);
  return temp->GetVal();
}

const float& InitFloat(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigFloat(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigFloat* temp = static_cast<config_types::ConfigFloat*>(t);
  return temp->GetVal();
}

const std::string& InitString(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigString(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigString* temp =
      static_cast<config_types::ConfigString*>(t);
  return temp->GetVal();
}

const Eigen::Vector2f& InitVector2f(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigVector2f(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigVector2f* temp =
      static_cast<config_types::ConfigVector2f*>(t);
  return temp->GetVal();
}

const bool& InitBool(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigBool(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigBool* temp = static_cast<config_types::ConfigBool*>(t);
  return temp->GetVal();
}

const Eigen::Vector2d& InitVector2d(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigVector2d(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigVector2d* temp =
      static_cast<config_types::ConfigVector2d*>(t);
  return temp->GetVal();
}

const Eigen::Vector3d& InitVector3d(const std::string& key) {
  config[key] = std::unique_ptr<config_types::ConfigInterface>(
      new config_types::ConfigVector3d(key));
  config_types::ConfigInterface* t = config.find(key)->second.get();
  config_types::ConfigVector3d* temp =
      static_cast<config_types::ConfigVector3d*>(t);
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

void InitDaemon(const std::vector<std::string>& files) {
  int length = 0;
  char buffer[EVENT_BUF_LEN];

  // Initialize inotify
  int fd = inotify_init();
  if (fd < 0) {
    std::cerr << "ERROR: Couldn't initialize inotify" << std::endl;
    exit(-1);
  }

  // Load in the files for the first time
  LuaRead(files);

  // Add all the files to be watched
  for (const std::string& f : files) {
    int wd = inotify_add_watch(fd, f.c_str(), IN_MODIFY);
    if (wd == -1){
      std::cerr << "ERROR: Couldn't add watch to the file: " << f << std::endl;
      exit(-1);
    }
  }

  int epfd = epoll_create(1);
  if (epfd < 0) {
    std::cerr << "ERROR: Call to epoll_create failed." << std::endl;
  }

  epoll_event ready_to_read = {0};
  ready_to_read.data.fd = fd;
  ready_to_read.events = EPOLLIN;
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ready_to_read)) {
    std::cerr << "ERROR: Call to epoll_ctl failed." << std::endl;
  }

  epoll_event epoll_events;

  auto last_notify = std::chrono::system_clock::now();
  bool needs_update = false;

  // Loop forever, checking for changes to the files above
  while (is_running_) {
    // Wait for 50 ms for there to be an available inotify event
    int nr_events = epoll_wait(epfd, &epoll_events, 1, kInotifySleep);

    if (nr_events < 0) {
      // If the call to epoll_wait failed
      std::cerr << "ERROR: Call to epoll_wait failed." << std::endl;
      exit(-1);
    }
    if (nr_events > 0) {
      // Else if the inotify fd has recieved something that can be read
      length = read(fd, buffer, EVENT_BUF_LEN);
      if (length < 0) std::cerr << "ERROR: Inotify read failed" << std::endl;

      for (int i = 0; i < length;) {
        inotify_event* event = reinterpret_cast<inotify_event*>(&buffer[i]);
        if (event->mask & IN_MODIFY) {  // If the event was a modify event
          last_notify = std::chrono::system_clock::now();
          needs_update = true;
        }
        i += EVENT_SIZE + event->len;
      }
    }
    if (needs_update && std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now() - last_notify)
                                .count() > 2 * kInotifySleep) {
      LuaRead(files);
      needs_update = false;
    }
  }

  // Clean up
  close(epfd);
  close(fd);
}

void CreateDaemon(const std::vector<std::string>& files) {
  LuaRead(files);
  is_running_ = true;
  daemon_ = std::thread(InitDaemon, files);
}

void Stop() {
  is_running_ = false;
  if (daemon_.joinable()) daemon_.join();
}

}  // namespace Configuration Reader

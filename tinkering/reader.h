#pragma once

extern "C" {
#include <sys/epoll.h>
#include <sys/inotify.h>
#include <unistd.h>
}

#include <atomic>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "basetype.h"
#include "configtype.h"
#include "inttype.h"
#include "lua_script.h"

namespace reader {

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

static constexpr int kInotifySleep = 50;

std::unordered_map<std::string, std::unique_ptr<types::BaseType>> global_map_;
std::atomic_bool is_running_;
std::thread daemon_;

const int& InitInt(const std::string& key) {
  global_map_[key] = std::unique_ptr<types::BaseType>(new types::IntType(key));
  types::BaseType* base = global_map_[key].get();
  return static_cast<types::IntType*>(base)->GetVal();
}

void SetInt(const std::string& key, const int& value) {
  types::BaseType* base = global_map_[key].get();
  static_cast<types::IntType*>(base)->SetVal(value);
}

#define CFG_INT(name, key) const int& CFG_##name = ::reader::InitInt(key)

void ReadLua(const std::vector<std::string>& files) {
  // Create the LuaScript object
  lua_reading::LuaScript script(files);
  // Loop through the unordered map
  for (const auto& pair : global_map_) {
    // Create a temporary pointer because you can't static_cast a unique_ptr
    types::BaseType* t = pair.second.get();
    // Switch statement that serves as a runtime typecheck
    // See the ConfigInterface.h file for documentation on the ConfigType enum
    // and the GetType() function
    switch (pair.second->GetType()) {
      case (types::ConfigType::CINT):  // int
      {
        auto* temp = static_cast<types::IntType*>(t);
        temp->SetVal(&script);
        std::cout << pair.first << " (int) was set to " << temp->GetVal()
                  << std::endl;
        break;
      }
      /* case (types::ConfigType::CUINT):  // uint */
      /* { */
      /*   config_types::ConfigUint* temp = */
      /*       static_cast<config_types::ConfigUint*>(t); */
      /*   temp->SetVal(&script); */
      /*   std::cout << temp->GetKey() << " (uint) was set to " <<
       * temp->GetVal() */
      /*             << std::endl; */
      /*   break; */
      /* } */
      /* case (types::ConfigType::CDOUBLE):  // double */
      /* { */
      /*   config_types::ConfigDouble* temp = */
      /*       static_cast<config_types::ConfigDouble*>(t); */
      /*   temp->SetVal(&script); */
      /*   std::cout << temp->GetKey() << " (double) was set to " <<
       * temp->GetVal() */
      /*             << std::endl; */
      /*   break; */
      /* } */
      /* case (types::ConfigType::CFLOAT):  // float */
      /* { */
      /*   config_types::ConfigFloat* temp = */
      /*       static_cast<config_types::ConfigFloat*>(t); */
      /*   temp->SetVal(&script); */
      /*   std::cout << temp->GetKey() << " (float) was set to " <<
       * temp->GetVal() */
      /*             << std::endl; */
      /*   break; */
      /* } */
      /* case (types::ConfigType::CSTRING):  // string */
      /* { */
      /*   config_types::ConfigString* temp = */
      /*       static_cast<config_types::ConfigString*>(t); */
      /*   temp->SetVal(&script); */
      /*   std::cout << temp->GetKey() << " (string) was set to " <<
       * temp->GetVal() */
      /*             << std::endl; */
      /*   break; */
      /* } */
      /* case (types::ConfigType::CVECTOR2F):  // vector2f */
      /* { */
      /*   config_types::ConfigVector2f* temp = */
      /*       static_cast<config_types::ConfigVector2f*>(t); */
      /*   temp->SetVal(&script); */
      /*   std::cout << temp->GetKey() << " (Vector2f) was set to " */
      /*             << temp->GetVal() << std::endl; */
      /*   break; */
      /* } */
      /* case (types::ConfigType::CBOOL):  // bool */
      /* { */
      /*   config_types::ConfigBool* temp = */
      /*       static_cast<config_types::ConfigBool*>(t); */
      /*   temp->SetVal(&script); */
      /*   std::cout << temp->GetKey() << " (boolean) was set to " */
      /*             << temp->GetVal() << std::endl; */
      /*   break; */
      /* } */
      /* case (types::ConfigType::CVECTOR2D):  // vector2d */
      /* { */
      /*   config_types::ConfigVector2d* temp = */
      /*       static_cast<config_types::ConfigVector2d*>(t); */
      /*   temp->SetVal(&script); */
      /*   std::cout << temp->GetKey() << " (Vector2d) was set to " */
      /*             << temp->GetVal() << std::endl; */
      /*   break; */
      /* } */
      /* case (types::ConfigType::CVECTOR3D):  // vector3d */
      /* { */
      /*   config_types::ConfigVector3d* temp = */
      /*       static_cast<config_types::ConfigVector3d*>(t); */
      /*   temp->SetVal(&script); */
      /*   std::cout << temp->GetKey() << " (Vector3d) was set to " */
      /*             << temp->GetVal() << std::endl; */
      /*   break; */
      /* } */
      case (types::ConfigType::CNULL):
      default:  // null type: the type value used when a ConfigInterface is
                // constructed -> should never actually be used
        std::cerr << "ERROR: ConfigType enum has a value of null, this should "
                     "never happen!"
                  << std::endl;
        exit(-1);
        break;
    }
  }
}

void UpdateDaemon(const std::vector<std::string>& files) {
  int length = 0;
  char buffer[EVENT_BUF_LEN];

  // Initialize inotify
  int fd = inotify_init();
  if (fd < 0) {
    std::cerr << "ERROR: Couldn't initialize inotify" << std::endl;
    exit(-1);
  }

  // Add all the files to be watched
  for (const std::string& f : files) {
    int wd = inotify_add_watch(fd, f.c_str(), IN_MODIFY);
    if (wd == -1) {
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

  while (is_running_) {
    // Wait for 50 ms for there to be an available inotify event.
    int nr_events = epoll_wait(epfd, &epoll_events, 1, kInotifySleep);

    if (nr_events < 0) {
      // If the call to epoll_wait failed
      std::cerr << "ERROR: Call to epoll_wait failed." << std::endl;
      exit(-1);
    }

    if (nr_events > 0) {
      // If the inotify fd has recieved something that can be read.
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
      ReadLua(files);
      needs_update = false;
    }
  }
}

void CreateDaemon(const std::vector<std::string>& files) {
  is_running_ = true;
  ReadLua(files);
  daemon_ = std::thread(UpdateDaemon, files);
}

void StopDaemon() {
  is_running_ = false;
  if (daemon_.joinable()) {
    daemon_.join();
  }
}

}  // namespace reader

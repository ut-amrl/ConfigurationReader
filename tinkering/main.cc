#include <signal.h>
#include <chrono>
#include <iostream>

#include "my_cool_header.h"
#include "reader.h"

CFG_INT(foo_val, "foo");

std::atomic_bool should_shutdown(false);

void SigHandler(int signo) {
  if (signo == SIGINT) {
    std::cout << "Shutting down!\n";
    should_shutdown = true;
  }
}

int main() {
  if (signal(SIGINT, SigHandler) == SIG_ERR) {
    std::cout << "Cannot trap SigHandler!\n";
    exit(0);
  }
  reader::CreateDaemon({"hello.txt"});

  while (!should_shutdown) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Foo Value: " << CFG_foo_val << "\n";
  }

  reader::StopDaemon();
  std::cout << "Shut down!\n";

  return 0;
}

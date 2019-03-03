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

// Sample main
#include <chrono> // For testing purposes only
#include "reader.h"
#include "my_vars.h"

int main(int argc, char* argv[]){
  std::vector<std::string> files;
  if (argc == 2) {
    std::string t = argv[1];
    if (t == "-h" || t == "-help" || t == "--help") {
      configuration_reader::HelpText();
      return 0;
    }
    files.push_back(argv[1]);
  } else if(argc > 2) {
    for(int i=1; i<argc; i++){
      files.push_back(argv[i]);
    }
  } else {
    files.push_back(configuration_reader::kDefaultFileName);
  }

  configuration_reader::CreateDaemon(files);
  sleep(5);
  std::cout<<configuration_reader::CONFIG_test<<std::endl;
  std::cout<<configuration_reader::CONFIG_someInt<<std::endl;

  configuration_reader::Stop();
  return 0;
}
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
#include "config_reader.h"
#include "config_reader.cc"

using namespace std;

int main(int argc, char* argv[]){
  vector<string> files;
  if (argc == 2) {
    string t = argv[1];
    if (t == "-h" || t == "-help" || t == "--help") {
      ConfigReader::helptext();
      return 0;
    }
    files.push_back(argv[1]);
  } else if(argc > 2) {
    for(int i=1; i<argc; i++){
      files.push_back(argv[i]);
    }
  } else {
    files.push_back(DEFAULT_FILENAME);
  }

  ConfigReader r(files);
  r.init();
  return 0;
}
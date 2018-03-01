// Example Main for using the Configuration Reader class
// Copyright 2018 Ishan Khatri

#include "ConfigReader.h"
#include "ConfigReader.cpp"

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
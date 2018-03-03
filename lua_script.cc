// Copyright 2018 ikhatri@umass.edu
// College of Information and Computer Sciences,
// University of Massachusetts Amherst
// Based on source by Elias Daler
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
#include "lua_script.h"
#include <string.h>

// Constructor
LuaScript::LuaScript(const std::string& filename) {
  L = luaL_newstate();
  if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
    std::cout << "Error: failed to load (" << filename << ")" << std::endl;
    L = 0;
  }

  if (L) luaL_openlibs(L);
}

// Destructor for the LuaScript Object
LuaScript::~LuaScript() {
  if (L) lua_close(L);
}

void LuaScript::printError(const std::string& variableName,
                           const std::string& reason) {
  std::cout << "Error: can't get [" << variableName << "]. " << reason
            << std::endl;
}

// Wrapper to return an array of ints from Lua
std::vector<int> LuaScript::getIntVector(const std::string& name) {
  std::vector<int> v;
  lua_gettostack(name.c_str());
  if (lua_isnil(L, -1)) {  // array is not found
    return std::vector<int>();
  }
  lua_pushnil(L);
  while (lua_next(L, -2)) {
    v.push_back((int)lua_tonumber(L, -1));
    lua_pop(L, 1);
  }
  clean();
  return v;
}

// Wrapper to return an Eigen::Vector2f from Lua
/*Eigen::Vector2f LuaScript::getVector2f(const std::string& name){
  Eigen::Vector2f v;
  lua_gettostack(name.c_str());
  if (lua_isnil(L, -1)) {  // array is not found
    std::cout<<"Vector2f not found in Lua file"<<std::endl;
    return v;
  }
  lua_pushnil(L);
  int i = 0;
  while (lua_next(L, -2) && i<2) {
    v(i)=((float)lua_tonumber(L, -1));
    lua_pop(L, 1);
    i++;
  }
  clean();
  return v;
}*/

Eigen::Vector2f LuaScript::getVector2f(const std::string& name) {
  Eigen::Vector2f v;
  Eigen::Vector2f v2;
  lua_gettostack(name.c_str());
  if (lua_isnil(L, -1)) {  // array is not found
    std::cout << "Vector2f not found in Lua file" << std::endl;
    return v;
  }
  lua_pushnil(L);
  int i = 0;
  while (lua_next(L, -2) && i < 2) {
    if (strncmp(lua_typename(L, lua_type(L, -2)), "string", 6) == 0) {
      if (strncmp(lua_tostring(L, -2), "x", 1) == 0) {
        v(0) = ((float)lua_tonumber(L, -1));
      } else {
        v(1) = ((float)lua_tonumber(L, -1));
      }
      lua_pop(L, 1);
      i++;
    } else {
      std::cout << "ERROR: Key is not a string." << std::endl;
    }
  }
  clean();
  return v;
}

// Wrapper to return all the keys from a Lua table
std::vector<std::string> LuaScript::getTableKeys(const std::string& name) {
  std::string code =
      "function getKeys(name) "
      "s = \"\""
      "for k, v in pairs(_G[name]) do "
      "    s = s..k..\",\" "
      "    end "
      "return s "
      "end";                         // function for getting table keys
  luaL_loadstring(L, code.c_str());  // execute code
  lua_pcall(L, 0, 0, 0);
  lua_getglobal(L, "getKeys");  // get function
  lua_pushstring(L, name.c_str());
  lua_pcall(L, 1, 1, 0);  // execute function
  std::string test = lua_tostring(L, -1);
  std::vector<std::string> strings;
  std::string temp = "";
  std::cout << "TEMP:" << test << std::endl;
  for (unsigned int i = 0; i < test.size(); i++) {
    if (test.at(i) != ',') {
      temp += test.at(i);
    } else {
      strings.push_back(temp);
      temp = "";
    }
  }
  clean();
  return strings;
}

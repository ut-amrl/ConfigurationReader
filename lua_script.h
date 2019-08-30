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
#ifndef CONFIGREADER_LUASCRIPT_H_
#define CONFIGREADER_LUASCRIPT_H_

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>

extern "C" {
#include "lua5.1/lauxlib.h"
#include "lua5.1/lua.h"
#include "lua5.1/lualib.h"
}

class LuaScript {
 public:
  LuaScript(const std::vector<std::string>& files);
  ~LuaScript();
  void printError(const std::string& variableName, const std::string& reason);
  std::vector<int> getIntVector(const std::string& name);
  Eigen::Vector2f getVector2f(const std::string& name);
  Eigen::Vector2d getVector2d(const std::string& name);
  Eigen::Vector3d getVector3d(const std::string& name);
  std::vector<std::string> getTableKeys(const std::string& name);

  inline void clean() {
    int n = lua_gettop(L);
    lua_pop(L, n);
  }

  template <typename T>
  T get(const std::string& variableName) {
    if (!L) {
      printError(variableName, "Script is not loaded");
      return lua_getdefault<T>();
    }

    T result;
    if (lua_gettostack(variableName)) {  // variable succesfully on top of stack
      result = lua_get<T>(variableName);
    } else {
      result = lua_getdefault<T>();
    }

    clean();
    return result;
  }

  bool lua_gettostack(const std::string& variableName) {
    level = 0;
    std::string var = "";
    for (unsigned int i = 0; i < variableName.size(); i++) {
      if (variableName.at(i) == '.') {
        if (level == 0) {
          lua_getglobal(L, var.c_str());
        } else {
          lua_getfield(L, -1, var.c_str());
        }

        if (lua_isnil(L, -1)) {
          printError(variableName, var + " is not defined");
          return false;
        } else {
          var = "";
          level++;
        }
      } else {
        var += variableName.at(i);
      }
    }
    if (level == 0) {
      lua_getglobal(L, var.c_str());
    } else {
      lua_getfield(L, -1, var.c_str());
    }
    if (lua_isnil(L, -1)) {
      printError(variableName, var + " is not defined");
      return false;
    }

    return true;
  }

  // Generic get
  template <typename T>
  T lua_get(const std::string& variableName) {
    return 0;
  }

  template <typename T>
  T lua_getdefault() {
    return 0;
  }

 private:
  lua_State* L;
  std::string filename;
  int level;
};

// Specializations

template <>
inline bool LuaScript::lua_get<bool>(const std::string& variableName) {
  return (bool)lua_toboolean(L, -1);
}

template <>
inline float LuaScript::lua_get<float>(const std::string& variableName) {
  if (!lua_isnumber(L, -1)) {
    printError(variableName, "Not a number");
  }
  return (float)lua_tonumber(L, -1);
}

template <>
inline int LuaScript::lua_get<int>(const std::string& variableName) {
  if (!lua_isnumber(L, -1)) {
    printError(variableName, "Not a number");
  }
  return (int)lua_tonumber(L, -1);
}

template <>
inline unsigned int LuaScript::lua_get<unsigned int>(
    const std::string& variableName) {
  if (!lua_isnumber(L, -1)) {
    printError(variableName, "Not a number");
  }
  return (unsigned int)lua_tonumber(L, -1);
}

template <>
inline double LuaScript::lua_get<double>(const std::string& variableName) {
  if (!lua_isnumber(L, -1)) {
    printError(variableName, "Not a number");
  }
  return (double)lua_tonumber(L, -1);
}

template <>
inline std::string LuaScript::lua_get<std::string>(
    const std::string& variableName) {
  std::string s = "null";
  if (lua_isstring(L, -1)) {
    s = std::string(lua_tostring(L, -1));
  } else {
    printError(variableName, "Not a string");
  }
  return s;
}

template <>
inline std::string LuaScript::lua_getdefault<std::string>() {
  return "null";
}

#endif

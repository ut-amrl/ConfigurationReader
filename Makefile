CXX = clang++
FLAGS = -std=c++11
OBJS = LuaScript.o ConfigInterface.o ConfigVar.o
FORMAT = clang-format
FFLAGS = -i --style=Google
FFILES = reader.cpp LuaScript.cpp LuaScript.h ConfigInterface.h ConfigInterface.cpp ConfigVar.h ConfigVar.cpp

.DEFAULT = all

all: reader

reader: reader.cpp $(OBJS)
	$(CXX) $(FLAGS) $^ -o reader -L "../../lua-5.3.4/src/" -llua -ldl

luascript.o: LuaScript.cpp LuaScript.h
	$(CXX) $(FLAGS) -c LuaScript.cpp

configinterface.o: ConfigInterface.h ConfigInterface.cpp
	$(CXX) $(FLAGS) -c ConfigInterface.cpp

configvar.o: ConfigVar.h ConfigVar.cpp
	$(CXX) $(FLAGS) -c ConfigVar.cpp

format:
	$(FORMAT) $(FFLAGS) $(FFILES)

clean:
	rm reader LuaScript.o ConfigVar.o ConfigInterface.o
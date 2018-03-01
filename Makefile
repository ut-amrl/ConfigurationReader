CXX = clang++
FLAGS = -std=c++11 -IConfigTypes/
OBJS = LuaScript.o ConfigInterface.o ConfigInt.o ConfigUint.o ConfigDouble.o ConfigFloat.o ConfigString.o ConfigVector2f.o #ConfigReader.o
FORMAT = clang-format
FFLAGS = -i --style=Google
FFILES = reader.cpp ConfigReader.h ConfigReader.cpp LuaScript.cpp LuaScript.h ConfigTypes/*.h ConfigTypes/*.cpp

VPATH = ConfigTypes/

.DEFAULT = all

all: main

#reader: reader.cpp $(OBJS)
#	$(CXX) $(FLAGS) $^ -o reader -L "../../lua-5.3.4/src/" -llua -ldl

main: main.cpp $(OBJS)
	$(CXX) $(FLAGS) $^ -o ConfigReader -L "../../lua-5.3.4/src/" -llua -ldl

configreader.o: ConfigReader.h ConfigReader.cpp
	$(CXX) $(FLAGS) -c ConfigReader.cpp

luascript.o: LuaScript.cpp LuaScript.h
	$(CXX) $(FLAGS) -c LuaScript.cpp

configinterface.o: ConfigInterface.h ConfigInterface.cpp
	$(CXX) $(FLAGS) -c ConfigInterface.cpp

configint.o: ConfigInt.h ConfigInt.cpp
	$(CXX) $(FLAGS) -c ConfigInt.cpp

configuint.o: ConfigUint.h ConfigUint.cpp
	$(CXX) $(FLAGS) -c ConfigUint.cpp

configdouble.o: ConfigDouble.h ConfigDouble.cpp
	$(CXX) $(FLAGS) -c ConfigDouble.cpp

configfloat.o: ConfigFloat.h ConfigFloat.cpp
	$(CXX) $(FLAGS) -c ConfigFloat.cpp

configstring.o: ConfigString.h ConfigString.cpp
	$(CXX) $(FLAGS) -c ConfigString.cpp

configvector2f: ConfigVector2f.h ConfigVector2f.cpp
	$(CXX) $(FLAGS) -c ConfigVector2f.cpp

format:
	$(FORMAT) $(FFLAGS) $(FFILES)

clean:
	rm reader ConfigReader $(OBJS)
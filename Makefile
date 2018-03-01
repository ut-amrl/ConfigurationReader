CXX = clang++
FLAGS = -std=c++11 -Iconfig_types/
OBJS = lua_script.o config_interface.o config_int.o config_unsigned_int.o config_double.o config_float.o config_string.o config_vector2f.o
FORMAT = clang-format
FFLAGS = -i --style=Google
FFILES = reader.cc config_reader.h config_reader.cc lua_script.cc lua_script.h config_types/*.h config_types/*.cc

VPATH = config_types/

.DEFAULT = all

all: main reader

reader: reader.cc $(OBJS)
	$(CXX) $(FLAGS) $^ -o reader -L "../../lua-5.3.4/src/" -llua -ldl

main: main.cc $(OBJS)
	$(CXX) $(FLAGS) $^ -o class_reader -L "../../lua-5.3.4/src/" -llua -ldl

lua_script.o: lua_script.h lua_script.cc
	$(CXX) $(FLAGS) -c lua_script.cc

config_interface.o: config_interface.h config_interface.cc
	$(CXX) $(FLAGS) -c config_types/config_interface.cc

config_int.o: config_int.h config_int.cc
	$(CXX) $(FLAGS) -c config_types/config_int.cc

config_unsigned_int.o: config_unsigned_int.h config_unsigned_int.cc
	$(CXX) $(FLAGS) -c config_types/config_unsigned_int.cc

config_double.o: config_double.h config_double.cc
	$(CXX) $(FLAGS) -c config_types/config_double.cc

config_float.o: config_float.h config_float.cc
	$(CXX) $(FLAGS) -c config_types/config_float.cc

config_string.o: config_string.h config_string.cc
	$(CXX) $(FLAGS) -c config_types/config_string.cc

config_vector2f: config_vector2f.h config_vector2f.cc
	$(CXX) $(FLAGS) -c config_types/config_vector2f.cc

format:
	$(FORMAT) $(FFLAGS) $(FFILES)

clean:
	rm reader class_reader $(OBJS)
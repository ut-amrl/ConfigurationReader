FLAGS := -std=c++11 -Wall
INCLUDES := -lpthread -latomic -llua -ldl -g -I/usr/local/include

all: main.o lua_script.o
	clang++ $(FLAGS) lua_script.o main.o $(INCLUDES) -o tinkering

main.o: main.cc
	clang++ -c $(FLAGS) main.cc

lua_script.o: lua_script.cc
	clang++ -c $(FLAGS) lua_script.cc

clean:
	rm -rf *.o tinkering || true

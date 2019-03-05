FLAGS := -std=c++11 -Wall
INCLUDES := -lpthread -latomic -llua -ldl -g -I/usr/local/include

all: main.o lua_script.o
	clang++ $(FLAGS) lua_script.o main.o $(INCLUDES) -o tinkering

main.o: main.cpp
	clang++ -c $(FLAGS) main.cpp

lua_script.o: lua_script.cpp
	clang++ -c $(FLAGS) lua_script.cpp

clean:
	rm -rf *.o tinkering || true

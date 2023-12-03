CC=g++
CFLAGS=-Wall -Wextra -std=c++17

all: main

main: main.cpp Grafos.hpp
	$(CC) $(CFLAGS) main.cpp -o main

clean:
	rm -f main

COMPILER = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -fsanitize=address
ETAP_FLAGS = -D ETAP1

.PHONY: run all clean

run: all
	./main

all: main

# TODO

main: main.o Performance.o
	${COMPILER} ${CXXFLAGS} main.o Performance.o -o main

main.o: main.cpp
	${COMPILER} ${CXXFLAGS} -D ETAP1 -c main.cpp -o main.o

Performance.o: Performance.cpp Performance.hpp
	${COMPILER} ${CXXFLAGS} -c Performance.cpp -o Performance.o

clean:
	rm -f *.o main

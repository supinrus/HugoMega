all:
	g++ hugomain.cpp -o hugomain -std=c++17 -Wall -lSDL2
debug:
	g++ hugomain.cpp -o hugomain -std=c++17 -Wall -lSDL2 -g

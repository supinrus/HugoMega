CXX_FLAGS := -std=c++17 -Wall $(shell pkg-config --cflags sdl2)
LD_FLAGS := $(shell pkg-config --libs sdl2)
CXX := g++

all:
	$(CXX) hugomain.cpp -o hugomain $(CXX_FLAGS) $(LD_FLAGS)
debug:
	$(CXX) hugomain.cpp -o hugomain $(CXX_FLAGS) $(LD_FLAGS) -g

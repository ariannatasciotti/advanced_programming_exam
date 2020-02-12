SRC = benchmark.cpp
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14 -I..

EXE = $(SRC:.cpp=.x)

VPATH = ..

.SUFFIXES:
SUFFIXES =

.SUFFIXES: .cpp .x


all: $(EXE)


.PHONY: all

%.x: %.cpp

	$(CXX)  $< -o $@ $(CXXFLAGS)


clean:
		rm -f $(EXE) *~

.PHONY: clean

benchmark.x: iterator.hpp node.hpp bst.hpp

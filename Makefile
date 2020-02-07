SRC = main.cpp
HEADERS = iterator.hpp node.hpp bst.hpp
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

EXE = $(SRC:.cpp=.x)

all: $(EXE)

.PHONY: all

%.x: %.cpp

	$(CXX) $< -o $@ $(CXXFLAGS)


clean:
		rm -f $(EXE) *~ *.x

.PHONY: clean

main.x: iterator.hpp node.hpp bst.hpp
SRC = main.cpp
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14 -DTEST
EXE = $(SRC:.cpp=.x)

.SUFFIXES:
SUFFIXES =

.SUFFIXES: .cpp .x


all: $(EXE)


.PHONY: all

%.x: %.cpp

	$(CXX) $< -o $@ $(CXXFLAGS)


documentation: doxygen/doxy.in
	doxygen $^

.PHONY: documentation


clean:
		rm -f $(EXE) *~

.PHONY: clean

main.x: iterator.hpp node.hpp bst.hpp

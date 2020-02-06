SRC = main.cpp
HEADERS = iterator.hpp node.hpp bst.hpp
CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++14

EXE = $(SRC:.cpp=.x)

all: $(EXE)

.PHONY: all

%.x: %.cpp

	$(CXX) $< -o $@ $(CXXFLAGS)

format: $(SRC) $(HEADERS) main.cpp
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this command"

.PHONY: format


clean:
		rm -f $(EXE) *~ *.x

.PHONY: clean

main.x: iterator.hpp node.hpp bst.hpp


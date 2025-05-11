CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = main.cpp suffix_tree.cpp
HDR = suffix_tree.h
OBJ = $(SRC:.cpp=.o)

TARGET = suffix_tree

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(OBJ) $(TARGET)

.phony: all clean
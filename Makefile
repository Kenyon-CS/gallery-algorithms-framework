CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -pedantic
INCLUDES := -Iinclude

SRC := \
	src/main.cpp \
	src/Parser.cpp \
	src/Util.cpp \
	src/Evaluator.cpp \
	src/GreedyAlgorithm.cpp \
	algorithms/RandomAlgorithm.cpp

OBJ := $(SRC:.cpp=.o)
TARGET := planner

ifeq ($(OS),Windows_NT)
	TARGET := planner.exe
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET) data/gallery.yaml data/show.yaml greedy data/scoring.yaml

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean

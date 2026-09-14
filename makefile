CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lopengl32 -llua -lglfw3 -lgdi32 -lwinmm

TARGET = luacut.exe

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)

.PHONY: all build run debug clean

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(TARGET)

debug: CXXFLAGS += -g -O0
debug: clean build
	gdb ./$(TARGET)

clean:
	rm -rf build $(TARGET)
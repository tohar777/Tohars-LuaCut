CXX = g++
CC = gcc

CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
CFLAGS = -Wall -Wextra -Iinclude

LDFLAGS = -Llib -lopengl32 -llua -lglfw3 -lgdi32 -lwinmm

TARGET = luacut.exe

CPP_SRC = $(wildcard src/*.cpp)
C_SRC = $(wildcard src/*.c)

CPP_OBJ = $(CPP_SRC:src/%.cpp=build/%.o)
C_OBJ = $(C_SRC:src/%.c=build/%.o)

OBJ = $(CPP_OBJ) $(C_OBJ)

.PHONY: all build run debug clean

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: build
	./$(TARGET)

debug: CXXFLAGS += -g -O0
debug: CFLAGS += -g -O0
debug: clean build
	gdb ./$(TARGET)

clean:
	rm -rf build $(TARGET)
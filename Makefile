# Variables
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lglfw -lGLEW -lcunit -framework OpenGL

# Default
all: build

# Build
build:
	make clean
	mkdir -p build
	cd build && conan install .. --build=missing
	cd build && cmake ..
	cd build && make

# Cleanup
clean:
	rm -rf build

# Start application
start:
	./build/bin/app

# Test
test:
	make build && cd build/bin && ./tests

.PHONY: all build clean start test

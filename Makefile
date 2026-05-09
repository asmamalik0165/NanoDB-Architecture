CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

SOURCES = src/main.cpp src/DataValue.cpp src/BufferPool.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: bin/nanodb

bin/nanodb: $(SOURCES)
	@mkdir -p bin logs
	$(CXX) $(CXXFLAGS) -o bin/nanodb $(SOURCES)
	@echo "Build complete: bin/nanodb"

run: bin/nanodb
	./bin/nanodb

clean:
	rm -rf bin build logs/*.log

.PHONY: all run clean
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

all: bin/nanodb

bin/nanodb: src/main.cpp
	@mkdir -p bin logs
	$(CXX) $(CXXFLAGS) -o bin/nanodb src/main.cpp
	@echo "Build complete!"

run: bin/nanodb
	./bin/nanodb

clean:
	rm -rf bin build logs/*.log

.PHONY: all run clean
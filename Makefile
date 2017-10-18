SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp, obj/%.o, $(SOURCES))
CFLAGS := $(shell pkg-config --cflags sdl2)
LDFLAGS := $(shell pkg-config --libs sdl2)
COMMON := -g -O2


all: bin/game

run: bin/game
	@$<

bin/game: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(COMMON) $(OBJECTS) -o $@

obj/%.o: src/%.cpp
	$(CXX) -c $(CFLAGS) $(COMMON) $< -o $@

clean:
	@rm -rf obj
	@mkdir obj
	@rm -rf bin
	@mkdir bin

.PHONY: all run clean

.SUFFIXES: .cpp .o

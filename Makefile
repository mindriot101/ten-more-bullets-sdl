SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp, obj/%.o, $(SOURCES))
DEPS := $(OBJECTS:.o=.d)
CFLAGS := -Iinclude $(shell pkg-config --cflags sdl2) -MMD -MP
LDFLAGS := $(shell pkg-config --libs sdl2)
OPT := -O2
COMMON := -g $(OPT) -std=c++11 -Wall -Wextra


all: bin/game

run: bin/game
	@$<

debug: bin/game
	lldb $<

bin/game: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(COMMON) $(OBJECTS) -o $@

obj/%.o: src/%.cpp
	$(CXX) -c $(CFLAGS) $(COMMON) $< -o $@

clean:
	@rm -rf obj
	@mkdir obj
	@rm -rf bin
	@mkdir bin

-include $(DEPS)

.PHONY: all run clean debug

.SUFFIXES: .cpp .o

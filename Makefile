SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp, obj/%.o, $(SOURCES))


all: bin/game

run: bin/game
	@$<

bin/game: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

obj/%.o: src/%.cpp
	$(CXX) -c $< -o $@

clean:
	@rm -rf obj
	@mkdir obj
	@rm -rf bin
	@mkdir bin

.PHONY: all run clean

.SUFFIXES: .cpp .o

CC = gcc
CFLAGS = -g -Wall -Werror -Wpedantic
LDFLAGS =

CFLAGS += `pkg-config --cflags sdl2`
LDFLAGS += `pkg-config --libs sdl2`

LDFLAGS += `pkg-config --libs SDL2_ttf`

OUTPUT = ./bin/main

cfiles = $(wildcard src/*.c)
objects = $(cfiles:src/%.c=bin/%.o)

main: $(objects)
	$(CC) -o $(OUTPUT) $(objects) $(CFLAGS) $(LDFLAGS)

$(objects):
	$(CC) -c $(@:bin/%.o=src/%.c) -o $@ $(CFLAGS) $(LDFLAGS)

run: main
	$(OUTPUT)

clean:
	rm bin/*

.PHONY: main run clean

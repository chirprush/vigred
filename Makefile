CC := gcc
CFLAGS := -g -Wall -Werror -Wpedantic -Wextra
LDFLAGS := -Iinclude

CFLAGS += `pkg-config --cflags sdl2`
CFLAGS += `pkg-config --cflags SDL2_ttf`

LDFLAGS += `pkg-config --libs sdl2`
LDFLAGS += `pkg-config --libs SDL2_ttf`

LIB_SRCS := $(wildcard lib/*.c)
LIB_OBJS := $(LIB_SRCS:lib/%.c=bin/%.o)

BIN_SRCS := $(wildcard src/*.c)
BIN_OBJS := $(BIN_SRCS:src/%.c=bin/%.o)

bin/vigred: bin/libvigred.a $(BIN_OBJS)
	$(CC) -o bin/vigred $(BIN_OBJS) -Lbin -lvigred $(CFLAGS) $(LDFLAGS)

bin/libvigred.a: $(LIB_OBJS)
	ar rcs bin/libvigred.a $(LIB_OBJS)

bin/%.o: src/%.c
	$(CC) -c $< -o $@ -Lbin -lvigred $(CFLAGS) $(LDFLAGS)

bin/%.o: lib/%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm bin/*

.PHONY: clean

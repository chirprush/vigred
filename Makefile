CC := gcc
CFLAGS := -g -Wall -Werror -Wpedantic -Wextra
LDFLAGS := -Iinclude

CFLAGS += `pkg-config --cflags cairo`
LDFLAGS += `pkg-config --libs cairo`

LIB_SRCS := $(wildcard lib/*.c)
LIB_OBJS := $(LIB_SRCS:lib/%.c=bin/%.o)

BIN_SRCS := $(wildcard src/*.c)
BIN_OBJS := $(BIN_SRCS:src/%.c=bin/%.o)

bin/vigred: bin/libvigred.a $(BIN_OBJS)
	$(CC) -o bin/vigred $(BIN_OBJS) $(CFLAGS) $(LDFLAGS) -Lbin -lvigred

bin/libvigred.a: $(LIB_OBJS)
	ar rcs bin/libvigred.a $(LIB_OBJS)

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS) -Lbin -lvigred

bin/%.o: lib/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm bin/*

.PHONY: clean

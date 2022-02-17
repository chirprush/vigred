CC := gcc
CFLAGS := -g -Wall -Werror -Wpedantic -Wextra -Wswitch-enum -Wconversion
LDFLAGS := -fPIC -shared -lvigred

BIN_SRCS := $(shell find src -name '*.c')
BIN_OBJS := $(BIN_SRCS:src/%.c=bin/%.o)

install: bin/init.so
	cp bin/init.so ~/.config/vigred/init.so

bin/init.so: $(BIN_OBJS)
	$(CC) -o bin/init.so $(BIN_OBJS) $(CFLAGS) $(LDFLAGS)

bin/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf bin/*

.PHONY: install clean

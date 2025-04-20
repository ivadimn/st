DEBUG=-g
CC=gcc
CFLAGS ?= -Wall -Wextra -std=c11 -pedantic \
	$(shell pkg-config --libs --cflags gtk4) \
	$(DEBUG)
BINARY = test

default: $(BINARY)

clean:
	rm -f $(BINARY)


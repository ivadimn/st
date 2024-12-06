CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic 
LDFLAGS=-lX11

BINARY=xl

build: mainb.c
	$(CC) $(CFLAGS) mainb.c -o xl $(LDFLAGS)

clean:
	rm -f $(BINARY)

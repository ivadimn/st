CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic 
LDFLAGS=-lX11

BINARY=xl

build: over.c
	$(CC) $(CFLAGS) over.c -o xl $(LDFLAGS)

clean:
	rm -f $(BINARY)

CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic 
LDFLAGS=-lX11

BINARY=xl

build: mains.c
	$(CC) $(CFLAGS) mains.c -o xl $(LDFLAGS)

clean:
	rm -f $(BINARY)

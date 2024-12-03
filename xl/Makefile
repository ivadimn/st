CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic 
LDFLAGS=-lX11

BINARY=xl

build: main.c
	$(CC) $(CFLAGS) main.c -o xl $(LDFLAGS)

clean:
	rm -f $(BINARY)

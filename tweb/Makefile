
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic

all: build

build: tclient.c ../lib/log.c ../lib/unp.c
	$(CC) $(CFLAGS) tclient.c ../lib/log.c ../lib/unp.c -o tclient 

clean:
	rm -rf tclient
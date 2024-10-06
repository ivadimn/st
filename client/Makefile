
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic

all: client clientio server

client: tcp_client.c ../lib/log.c
	$(CC) $(CFLAGS) tcp_client.c ../lib/log.c -o tcp_client 

clientio: tcp_clientio.c ../lib/log.c
	$(CC) $(CFLAGS) tcp_clientio.c ../lib/log.c -o tcp_clientio -luring

server: tcp_server.c ../lib/log.c
	$(CC) $(CFLAGS) tcp_server.c ../lib/log.c -o tcp_server -luring

clean:
	rm -rf tcp_client tcp_clientio
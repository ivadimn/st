
PROG=test
FILES=dict.c utils.c
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic -Wno-unused-parameter
LIBS=-L../lib -lutils `pkg-config --libs libssl libcrypto`

$(PROG): $(PROG).c 
	$(CC) $(CFLAGS) $(PROG).c $(FILES) -o $(PROG) $(LIBS)

clean:
	rm -rf $(PROG)

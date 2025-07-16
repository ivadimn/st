
PROG=main
FILES=animal.c cat.c duck.c
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic -Wno-unused-parameter
LIBS=`pkg-config --libs libssl libcrypto`

$(PROG): $(PROG).c 
	$(CC) $(CFLAGS) $(PROG).c $(FILES) -o $(PROG) $(LIBS)

clean:
	rm -rf $(PROG)

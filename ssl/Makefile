
PROG=md5
FILES=md5.c
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic -Wno-unused-parameter
LIBS=`pkg-config --libs libssl libcrypto`

$(PROG): $(PROG).c 
	$(CC) $(CFLAGS) $(PROG).c -o $(PROG) $(LIBS)

clean:
	rm -rf $(PROG)

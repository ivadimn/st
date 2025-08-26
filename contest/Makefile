
PROG=main
FILES=
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic -Wno-unused-parameter `pkg-config --cflags libpq`
LIBS=  -L../lib -lutils `pkg-config --libs libpq`

$(PROG): $(PROG).c 
	$(CC) $(CFLAGS) $(PROG).c $(FILES) -o $(PROG) $(LIBS)

clean:
	rm -rf $(PROG)

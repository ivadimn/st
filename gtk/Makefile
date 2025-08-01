
PROG=four
FILES=
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic `pkg-config --cflags gtk4`
LIBS=`pkg-config --libs gtk4`

$(PROG): $(PROG).c $(FILES)
	$(CC) $(CFLAGS) $(PROG).c $(FILES) -o $(PROG) $(LIBS)

clean:
	rm -rf $(PROG)

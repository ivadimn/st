
PROG=app
FILES=log.c db/db.c views/table.c views/menu.c
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic `pkg-config --cflags gtk+-3.0 sqlite3`
LIBS=`pkg-config --libs gtk+-3.0 sqlite3`

$(PROG): $(PROG).c $(FILES)
	$(CC) $(CFLAGS) $(PROG).c $(FILES)  -o $(PROG) $(LIBS)

clean:
	rm -rf $(PROG)

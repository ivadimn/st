
PROG=main
FILES=db.c log.c entity.c pd.c vstrex.c
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic -Wno-unused-parameter `pkg-config --cflags sqlite3` 
LIBS=`pkg-config --libs sqlite3`

$(PROG): $(PROG).c 
	$(CC) $(CFLAGS) $(PROG).c $(FILES) -o $(PROG) $(LIBS)

clean:
	rm -rf $(PROG)

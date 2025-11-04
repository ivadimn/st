
PROG=main
FILES=connection.c person.c person_repository.c postgres.c param.c row.c
CC=gcc

CFLAGS=-Wall -Wextra -Wpedantic -Wno-unused-parameter `pkg-config --cflags libpq`
LIBS=  -L../lib -lutils `pkg-config --libs libpq`

$(PROG): $(PROG).c 
	$(CC) $(CFLAGS) $(PROG).c $(FILES) -o $(PROG) $(LIBS)

clean:
	rm -rf $(PROG)

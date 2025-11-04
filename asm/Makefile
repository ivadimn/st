
PROG=test
FILES=
ASM=nasm
LINK=ld

CFLAGS=-f elf64
LIBS=

$(PROG): $(PROG).asm 
	$(ASM) $(CFLAGS) $(PROG).asm $(FILES) -o $(PROG).o $(LIBS)
	$(LINK) -o $(PROG) $(PROG).o

clean:
	rm -rf $(PROG)  $(PROG).o

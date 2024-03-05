CC=gcc
CFLAGS=-Wall -Wextra -pedantic

pnm: main.o pnm.o
	$(CC) $(CFLAGS) -o pnm main.o pnm.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

pnm.o: pnm.c
	$(CC) $(CFLAGS) -c pnm.c

clean:
	rm -f pnm *.o

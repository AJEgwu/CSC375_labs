CC=gcc
CFLAGS=-g -Wall

all: wc map limits

wc: main.o word_count.o
	$(CC) $(CFLAGS) -o wc main.o word_count.o

map: map.o recurse.o
	$(CC) $(CFLAGS) -o map map.o recurse.o

limits: limits.o
	$(CC) $(CFLAGS) -o limits limits.o

clean:
	rm -f *.o wc map limits

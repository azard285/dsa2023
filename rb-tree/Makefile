CC = gcc
CFLAGS = -Wall

all: app

app: main.o rbtree.o
	$(CC) $(CFLAGS) -o app main.o rbtree.o

main.o: main.c rbtree.h
	$(CC) $(CFLAGS) -c main.c

rbtree.o: rbtree.c rbtree.h
	$(CC) $(CFLAGS) -c rbtree.c

clean:
	rm -f *.o
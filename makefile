CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm -std=gnu11
OBJ = Main.o LinkedList.o FileIO.o StringBuilder.o
EXEC = pipeline

pipeline: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

link: Main.c LinkedList.c FileIO.c StringBuilder.c
	$(CC) Main.c LinkedList.c FileIO.c StringBuilder.c 

main: Main.c 
	$(CC) $(CFLAGS) -c Main.c -g

linkedlist: LinkedList.c
	$(CC) $(CFLAGS) -c LinkedList.c -g 

fileio: FileIO.c
	$(CC) $(CFLAGS) -c FileIO.c -g

stringbuilder: StringBuilder.c
	$(CC) $(CFLAGS) -c StringBuilder.c -g

clean:
	rm -f $(EXEC) $(OBJ)
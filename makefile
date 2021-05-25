CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm -std=gnu11
OBJ = Main.o LinkedList.o FileIO.o StringBuilder.o CommandExecutor.o
EXEC = pipesim

pipesim: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

link: Main.c LinkedList.c FileIO.c StringBuilder.c CommandExecutor.c
	$(CC) Main.c LinkedList.c FileIO.c StringBuilder.c CommandExecutor.c

main: Main.c 
	$(CC) $(CFLAGS) -c Main.c

linkedlist: LinkedList.c
	$(CC) $(CFLAGS) -c LinkedList.c

fileio: FileIO.c
	$(CC) $(CFLAGS) -c FileIO.c

stringbuilder: StringBuilder.c
	$(CC) $(CFLAGS) -c StringBuilder.c 

commandexecutor: CommandExecutor.c
	$(CC) $(CFLAGS) -c CommandExecutor.c

test: LinkedListTest.c
	$(CC) $(CFLAGS) LinkedListTest.c LinkedList.c -o test

clean:
	rm -f $(EXEC) $(OBJ)
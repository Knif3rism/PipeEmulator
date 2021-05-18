CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm -std=gnu11
OBJ = Main.o LinkedList.o FileIO.o StringBuilder.o CommandExecutor.o
EXEC = pipeline

pipeline: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

link: Main.c LinkedList.c FileIO.c StringBuilder.c CommandExecutor.c
	$(CC) Main.c LinkedList.c FileIO.c StringBuilder.c CommandExecutor.c

main: Main.c 
	$(CC) -c Main.c -g

linkedlist: LinkedList.c
	$(CC) -c LinkedList.c -g 

fileio: FileIO.c
	$(CC) -c FileIO.c -g

stringbuilder: StringBuilder.c
	$(CC) -c StringBuilder.c -g

commandexecutor: CommandExecutor.c
	$(CC) -c CommandExecutor.c

clean:
	rm -f $(EXEC) $(OBJ)
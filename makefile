CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm
OBJ = Main.o LinkedList.o
EXEC = pipeline

pipeline: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

link: Main.c LinkedList.c
	$(CC) Main.c LinkedList.c 

main: Main.c 
	$(CC) -c Main.c -g

linkedlist: LinkedList.c
	$(CC) -c LinkedList.c -g 

clean:
	rm -f $(EXEC) $(OBJ)
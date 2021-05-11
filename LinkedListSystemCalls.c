/* name: Linked List with System Calls
 * author: Egan Chen
 * Date Created: 10/05/2021
 * Purpose: An implementation of a Linked List with no malloc
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "LinkedListSystemCalls.h"


LinkedList* newList(int fileSize, char* fileName)
{
    int fileDescriptor, status;
    size_t t_Size;

    int* mem_map;

    /* stat gives the file fileDescriptor of the file */
    struct stat statSize;
    struct LinkedList *newList;

    fileDescriptor = open(fileName, O_RDONLY);

    if (fileDescriptor < 0)
    {
        fprintf(stderr, "%s");
    }

    status = fstat(fileDescriptor, &statSize);

    if (status < 0)
    {
        fprintf(stderr, "%s");
    }

    t_Size = statSize.st_size;

    mem_map = mmap(0, fileDescriptor, PROT_READ, MAP_ANON, fileDescriptor, 0);

    newList = mmap(0, sizeof(LinkedList*), PROT_READ | PROT_WRITE, MAP_ANON, 0, 0);
    newList->head = NULL;
    newList->tail = NULL;
    newList->mem_map = mem_map;
}

void insertLast(LinkedList list, char* string)
{

}
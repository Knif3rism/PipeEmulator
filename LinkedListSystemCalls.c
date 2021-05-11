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
    int size, status;

    /* stat gives the file size of the file */
    struct stat fileSize;
    struct LinkedList *newList;

    size = open(fileName, O_RDONLY);

    if (size < 0)
    {
        fprintf(stderr, "%s", "Failed to open file");
    }

    status = fstat(size, &fileSize);

}
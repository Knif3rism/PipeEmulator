#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "StringBuilder.h"
#include "LinkedList.h"
#include "FileIO.h"

int main(int argc, char *argv[])
{
    int size, status;
    struct FileInformation theDeetz;
    struct LinkedList *list;
    Node_C *tempVar;


    /* if the user puts in 2 arguments after executing the file
     * then continue with normal program function
     */
    if (argc == 3)
    {
        theDeetz = fileToMem("test.txt");
        list = stringBuilderToList(theDeetz);
        tempVar = removeFirst(list);
        printf("%s", (char*) tempVar->value);
        tempVar = removeFirst(list);
        printf("%s", (char*) tempVar->value);
        tempVar = removeFirst(list);
        printf("%s", (char*) tempVar->value);
        tempVar = removeFirst(list);
        printf("%s", (char*) tempVar->value);

        freeList(list);

        status = close(theDeetz.fd);
        if (status != 0)
        {
            perror("cant close fd");
        }

        status = munmap((void*) theDeetz.file_map, theDeetz.fileSize);

    }
    else
    {
        printf("To use:\n./pipeline [inputfile] [outputfile]\n");
    }
    
    return 0;
}
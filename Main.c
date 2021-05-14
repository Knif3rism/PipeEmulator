#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "StringBuilder.h"
#include "LinkedList.h"
#include "FileIO.h"

int main(int argc, char *argv[])
{
    int size;
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
        size = getSize(list);
        printf("Size of list: %d\n", size);
        freeList(list);
    }
    else
    {
        printf("To use:\n./pipeline [inputfile] [outputfile]\n");
    }
    
    return 0;
}


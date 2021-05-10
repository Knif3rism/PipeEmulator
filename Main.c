#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int main(int argc, char *argv[])
{
    LinkedList *list;
    char *str; 


    /* if the user puts in 2 arguments after executing the file
     * then continue with normal program function
     */
    if (argc == 3)
    {
        str = (char*)malloc(sizeof(char));
        list = newLinkedList();
        insertFirst(list, (void*)str);
        freeList(list);
        printf("Hi you used 2 command line arguments good!\n");
    }
    else
    {
        printf("To use:\n./pipeline [inputfile] [outputfile]\n");
    }
    
    return 0;
}
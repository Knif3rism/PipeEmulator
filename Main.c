#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "LinkedList.h"
#include "FileIO.h"

int main(int argc, char *argv[])
{
    int ii = 0;
    struct FileInformation theDeetz;


    /* if the user puts in 2 arguments after executing the file
     * then continue with normal program function
     */
    if (argc == 3)
    {
        theDeetz = fileToMem("test.txt");
        for (ii = 0; ii < theDeetz.fileSize; ii++)
        {
            printf("%c", theDeetz.file_map[ii]);
        }
    }
    else
    {
        printf("To use:\n./pipeline [inputfile] [outputfile]\n");
    }
    
    return 0;
}
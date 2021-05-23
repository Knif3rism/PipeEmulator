#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "StringBuilder.h"
#include "LinkedList.h"
#include "FileIO.h"

int main(int argc, char *argv[])
{
    int status;
    struct FileInformation theDeetz;
    struct LinkedList *list;
    Node_C *tempNode;
    int count, ii = 0;
    char *program;
    char **arguments;    


    /* if the user puts in 2 arguments after executing the file
     * then continue with normal program function
     */
    if (argc == 3)
    {
        theDeetz = fileToMem("test.txt");
        list = stringBuilderToList(theDeetz);

        initiatorProcess(list);

        /* exec commands 


        tempNode = removeFirst(list);

        count = wordCount((char*) tempNode->value);

        arguments = splitString((char*) tempNode->value, count);
        program = stringAppender("/bin/", arguments[0]);
        printf("path: %s\n", program);
        
        while (arguments[ii] != NULL)
        {
            printf("ii(%d): %s\n", ii, arguments[ii]);
            ii++;
        }

        status = execv(program, arguments);
        if (status != 0)
        {
            perror("Something went wrong with execv()");
        }


        status = close(theDeetz.fd);
        if (status != 0)
        {
            perror("cant close fd");
        }

        status = munmap((void*) theDeetz.file_map, theDeetz.fileSize);*/

    }
    else
    {
        printf("To use:\n./pipeline [inputfile] [outputfile]\n");
    }
    
    return 0;
}
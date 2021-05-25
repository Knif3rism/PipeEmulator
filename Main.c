#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "CommandExecutor.h"
#include "StringBuilder.h"
#include "LinkedList.h"
#include "FileIO.h"

#define MSG_SIZE 2048

int main(int argc, char *argv[])
{
    struct FileInformation fileInfo;
    struct LinkedList *list;


    /* if the user puts in 2 arguments after executing the file
     * then continue with normal program function
     */
    if (argc == 2) /* no output file specified */
    {
        fileInfo = fileToMem(argv[1]);
        if (fileInfo.fd != 0)
        {
            list = stringBuilderToList(fileInfo);
            initiatorProcess(list, NULL);
        }
    }
    else if (argc == 3) /* output file specified */
    {
        fileInfo = fileToMem(argv[1]);
        if (fileInfo.fd != 0)
        {
            list = stringBuilderToList(fileInfo);
            initiatorProcess(list, argv[2]);
        }

    }
    else
    {
        write(1, "To use:\n./pipesim [inputfile] [outputfile]\n[outputfile] is optional, if you don't put in a file to output to, then output will be displayed on the terminal\n", 157);
    }
    
    return 0;
}
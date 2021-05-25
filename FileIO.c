#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "FileIO.h"

struct FileInformation fileToMem(char *fileName)
{
    int fd;
    char *file_map;

    struct FileInformation outFile;
    struct stat sb;

    /* Opens file and checks if it contains a length, if the file doesn't exist fstat returns -1*/
    fd = open(fileName, O_RDONLY);

    if (fstat(fd, &sb) == -1)
    {
        write(2, "Cannot get file size due to invalid file name\n", 47);
        outFile.fd = 0;
    }
    else
    {
            /*maps entire file to memory*/
            file_map = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

            outFile.fd = fd;
            outFile.sb = sb;
            outFile.file_map = file_map;
            outFile.fileSize = sb.st_size;
    }


    return outFile;
}

int writeOut(int fd[], char *fileName)
{
    int fileDesc;
    struct stat sb;

    fileDesc = open(fileName, O_WRONLY);

    if (fstat(fileDesc, &sb) == -1)
    {
        return 1;
    }
    else
    {
        write(fileDesc, STDOUT_FILENO, sb.st_size);
        return 0;
    }
}
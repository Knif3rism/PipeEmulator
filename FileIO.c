#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "FileIO.h"

struct FileInformation fileToMem(char *fileName)
{
    int fd;
    char *file_map;

    struct FileInformation outFile;
    struct stat sb;

    fd = open("./commandTest.txt", O_RDONLY);

    if (fstat(fd, &sb) == -1)
    {
        perror("Cannot get file size.\n");
    }

    file_map = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);


    printf("\nSize of file imported: %ld\n", sb.st_size);

    outFile.fd = fd;
    outFile.sb = sb;
    outFile.file_map = file_map;
    outFile.fileSize = sb.st_size;

    return outFile;
}
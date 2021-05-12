#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "FileIO.h"

struct FileInformation fileToMem(char *fileName)
{
    int fd, ii;
    char *file_map;

    struct FileInformation outFile;
    struct stat sb;

    fd = open("./test.txt", O_RDONLY, S_IRUSR | S_IWUSR);

    if (fstat(fd, &sb) == -1)
    {
        perror("Cannot get file size.\n");
    }

    file_map = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

    for (ii = 0; ii < sb.st_size; ii++)
    {
        printf("%c", file_map[ii]);
        if (file_map[ii] == EOF)
        {
            printf("\nThere is an EOF\n");
        }
    }

    printf("\n%ld\n", sb.st_size);

    outFile.fd = fd;
    outFile.sb = sb;
    outFile.file_map = file_map;
    outFile.fileSize = sb.st_size;

    return outFile;
}
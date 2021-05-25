#include <sys/stat.h>

#ifndef FileInfo
#define FileInfo

typedef struct FileInformation
    {
        int fd;
        int fileSize;
        char* file_map;
        struct stat sb;
    }FileInformation;

#endif

FileInformation fileToMem(char *fileName);
int writeOut(int fd[], char *fileName);
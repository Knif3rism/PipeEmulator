#include "LinkedList.h"
#ifndef commandexec
#define commandexec

typedef struct childProc 
    {
        int fd;
        int exitStatus;
        int signal;
    }childProc;

#endif

void cmdExec(LinkedList list, int pipeArr[]);
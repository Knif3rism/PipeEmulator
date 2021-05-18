#include "LinkedList.h"

typedef struct childProc 
    {
        int fd;
        int exitStatus;
        int signal;
    }childProc;

void cmdExec(LinkedList list, int pipeArr[]);
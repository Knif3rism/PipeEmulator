#include <unistd.h>
#include <sched.h>
#include <sys/mman.h>

#include "LinkedList.h"
#include "CommandExecutor.h"

#define STACK_SIZE 4096
#define MSG_SIZE 2048

void manager(LinkedList list)
{
    /*
     * pipeArr[0] - read only
     * pipeArr[1] - write only
     */
    int pipeArr[2];
    char *stack;
    char *stackTop;

    int status;
    pid_t pid;

    stack = mmap(NULL,  STACK_SIZE, PROT_READ | PROT_WRITE, 
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
                    
    if (stack == MAP_FAILED)
    {
        perror("mmap failed");
    }
    
    stackTop = stack + STACK_SIZE;

    /* spawn child processes based on the size of the linked list */

    pipe(pipeArr);

    clone((void (*cmdExec) (list, pipeArr)), STACK, )

    
}

void cmdExec(LinkedList list, int pipeArr[])
{
    int status;
    char* program;
    char** arguments;

    write(pipeArr[1], execv(program, arguments), MSG_SIZE);
    if (status != 0)
    {
        perror("Something went wrong with pipe");
    }

    
}

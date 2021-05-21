#include <unistd.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "StringBuilder.h"
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
    void (*cmdExec) (LinkedList, int);

    int status;
    pid_t pid;

    /*
    stack = mmap(NULL,  STACK_SIZE, PROT_READ | PROT_WRITE, 
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
                    
    if (stack == MAP_FAILED)
    {
        perror("mmap failed");
    }
    
    stackTop = stack + STACK_SIZE;

    pipe(pipeArr); */

    /* spawn child processes based on the size of the linked list */

    /* clone(&cmdExec, stackTop, SIGCHLD, list, pipeArr); */

    
}

void cmdExec(LinkedList *list, int pipeArr[])
{
    Node_C *tempNode;
    int status, count;
    char *program;
    char **arguments;

    tempNode = removeFirst(list);

    count = wordCount((char*) tempNode->value);

    arguments = splitString((char*) tempNode->value, count);
    program = stringAppender("/bin/", arguments[0]);
        

    status = execv(program, arguments);
    if (status != 0)
    {
        perror("Something went wrong with execv()");
    }


    
}

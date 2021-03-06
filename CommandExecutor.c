#define _GNU_SOURCE  
#include <unistd.h>
#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

#include "FileIO.h"
#include "StringBuilder.h"
#include "LinkedList.h"
#include "CommandExecutor.h"

#define STACK_SIZE 4096
#define MSG_SIZE 128

/* pipe as a global variable 
* fd[0] - read only
* fd[1] - write only
*/
int fd[2];

void initiatorProcess(LinkedList *list, char *fileName)
{

    int ii, size_list, status;
    char *stack;
    char *stackTop;

    pid_t pid;
    Node_C *tempNode;
    
    stack = mmap(NULL,  STACK_SIZE, PROT_READ | PROT_WRITE, 
                        MAP_SHARED | MAP_ANONYMOUS | MAP_STACK, -1, 0);
                    
    if (stack == MAP_FAILED)
    {
        write(2, "mmap failed", 12);
    }
    
    stackTop = stack + STACK_SIZE;

    pipe(fd);


    /* spawn child processes based on the size of the linked list */

    size_list = getSize(list);
    ii = 0;

    while (ii < size_list)
    {
        tempNode = removeFirst(list);        
        pid = clone(cmdExec, stackTop, SIGCHLD, tempNode);

        if (pid == -1)
        {
            write(2, "An error has occured in clone(): ", 34);
        }
        else /* parent */
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            waitpid(pid, NULL, 0);
        }

        ii++;
    }

    /*if (writeOut(fd, fileName))
    {
        write(2, "cannot write to file abort, print to screen", 44);
    }*/

}

int cmdExec(void *arg)
{
    Node_C *temp = (Node_C*) arg;
    int count, status;
    char *program;
    char **arguments;

    count = wordCount((char*) temp->value);

    arguments = splitString((char*) temp->value, count);
    program = stringAppender("/bin/", arguments[0]);

    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    status = execve(program, arguments, NULL);

    if (status == -1)
    {
        program = stringAppender("/usr/bin", arguments[0]);
        status = execve(program, arguments, NULL);
        if (status == -1)
        {
            write(2, "There was an error executing the command: ", 43);
        }
    }

    exit(0);
}
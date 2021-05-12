#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "FileIO.h"
#include "LinkedList.h"

void stringBuilderToList (struct FileInformation file)
{
    int ii, jj, nullify = 0, cursor = 0, status;
    char *temp;
    LinkedList *list;

    list = newList();
    
    
    for (ii = 0; ii < file.fileSize; ii++)
    {
        if (file.file_map[ii] != '\n')
        {
            nullify++;
        }
        else
        {
            temp = (char*) mmap(NULL, sizeof(char) + nullify, 
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

            for(jj = cursor; jj < nullify; jj++)
            {
                temp[jj] = file.file_map[jj];
                printf("%c", temp[jj]);
            }


            cursor = jj;

            status = munmap(temp, sizeof(char) + nullify);

            /*insertLast(list, (void*) temp, nullify+1);*/
        }
    }


    temp = (char*) mmap(NULL, sizeof(char) + nullify, 
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for(jj = cursor; jj < file.fileSize; jj++)
    {
        temp[jj] = file.file_map[jj];
        printf("%c", temp[jj]);
    }

    status = munmap(temp, sizeof(char) + nullify);

    printf("\n");

}
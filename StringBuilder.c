#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "FileIO.h"
#include "LinkedList.h"

LinkedList* stringBuilderToList (struct FileInformation file)
{
    int ii, jj, size_count;
    int nullify = 0, prev_nullify = 0, cursor = 0, temp_init;
    char *temp;
    LinkedList *list;

    list = newList();
    
    
    for (ii = 0; ii < file.fileSize; ii++)
    {
        /*if (file.file_map[ii] != '\n')
        {
            nullify++;
        }*/
        if (file.file_map[ii] == '\n')
        {
            nullify = ii;
            /* The else block sets our size_count to the index we find the \n char
             * subtract the last time we encountered the \n char, as that will set
             * the size of the given string. temp_init is to properly iterate through our
             * new memory allocation.
             */
            
            size_count = nullify - prev_nullify;
            temp_init = 0;
            temp = (char*) mmap(NULL, sizeof(char) * size_count, 
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

            for(jj = cursor; jj < nullify; jj++)
            {
                temp[temp_init] = file.file_map[jj];
                temp_init++;
            }

            if (temp[temp_init] != '\n')
            {
                temp[temp_init] = '\n';
            }

            cursor = jj;
            prev_nullify = nullify;

            insertLast(list, (void*) temp, nullify+1);
        }
    }

    /* we do this once again so that we can read the last line */
    temp_init = 0;

    temp = (char*) mmap(NULL, sizeof(char) + nullify, 
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for(jj = cursor; jj < file.fileSize; jj++)
    {
        temp[temp_init] = file.file_map[jj];
        temp_init++;
    }

    if (temp[temp_init] != '\n')
    {
        temp[temp_init] = '\n';
    }

    insertLast(list, (void*) temp, nullify+1);

    return list;
}
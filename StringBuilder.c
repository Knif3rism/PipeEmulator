#include <sys/mman.h>
#include "FileIO.h"
#include "LinkedList.h"

char* stringBuilderToList (struct FileInformation file)
{
    int ii, jj, nullify = 0;
    char *temp;
    LinkedList *list;

    list = newList();

    for (ii = 0; ii < file.fileSize; ii++)
    {
        if (file.file_map[ii] != '\0')
        {
            nullify++;
        }
        else
        {
            temp = mmap(NULL, sizeof(char)*(nullify+1), 
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED, -1, 0);

            for(jj = 0; jj < nullify; jj++)
            {
                temp[jj] = file.file_map[jj];
            }

            temp[nullify+1] = '\0';

            insertLast(list, (void*) temp, nullify+1);
        }
    }
}
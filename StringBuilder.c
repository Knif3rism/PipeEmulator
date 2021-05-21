#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "FileIO.h"
#include "LinkedList.h"

#define ARR_SIZE 64
#define STR_SIZE 256

LinkedList* stringBuilderToList (struct FileInformation file)
{
    int ii, jj, size_count;
    int nullify = 0, prev_nullify = 0, cursor = 0, temp_init;
    char *temp;
    LinkedList *list;

    list = newList();
    
    
    for (ii = 0; ii < file.fileSize; ii++)
    {
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

            if (temp[temp_init] != '\0')
            {
                temp[temp_init] = '\0';
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

    if (temp[temp_init] != '\0')
    {
        temp[temp_init] = '\0';
    }

    insertLast(list, (void*) temp, nullify+1);

    return list;
}


int wordCount(char* str)
{
    int ii = 0, space_counter = 0;

    while(str[ii] != '\0')
    {
        if (str[ii] == ' ')
        {
            space_counter++;
        }
        
        ii++;
    }

    /*we do +1 to the original counter as it will always miss the first word as it starts at 0*/
    return space_counter+1;
}


char** splitString(char* str, int amt_space)
{
    /*if we don't know word count then force to word count as param*/
    char** stringArr;
    int ii = 0, arr_count = 0, tempStr_size = 0, jj;
    char* tempStr;
    int tryIt;
    /*delimiter is always going to be space*/
    

    stringArr = mmap(NULL, ARR_SIZE, PROT_READ | PROT_WRITE, 
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    tempStr = mmap(NULL, STR_SIZE, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    do    
    {
        if ((str[ii] <= 'Z' && str[ii] >= 'A') || (str[ii] <= 'z' && str[ii] >= 'a') || 
            (str[ii] == '.') || (str[ii] == '-'))
        {  
            /*if it isn't a '-' character then we add on a char at the end of current string*/
            tempStr[tempStr_size] = str[ii];
            tempStr_size++;
        }
        else
        {  
            /*else there is a space char, then add the word into the string array*/
            if (str[ii] == '-')
            {
                printf("\noi mate: %d\n", str[ii]);
                for (jj = tempStr_size; jj >= 0; jj--)
                {
                    tempStr[jj+1] = tempStr[jj];
                }
                tempStr[0] = '-';
            }

            stringArr[arr_count] = tempStr;
            arr_count++;
            tempStr = mmap(NULL, STR_SIZE, PROT_READ | PROT_WRITE,
                           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            tempStr_size = 0;
        }

        ii++;
    }      
    while (str[ii] != '\0');      



    stringArr[arr_count] = tempStr;


    /*As execv needs null terminated strings, we add null at the end of the string*/
    stringArr[arr_count+1] = NULL;

    return stringArr;
}

/* this function assumes that str1 is a literal path */
char* stringAppender(char* str1, char* str2)
{
    int ii = 0, jj = 0;
    char* str3;

    str3 = mmap(NULL, STR_SIZE, PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    while (str1[ii] != '\0')
    {
        str3[ii] = str1[ii];
        ii++;
    }

    while (str2[jj] != '\0')
    {
        /* to ensure only printable characters are used */
        if ((str2[jj] < '~' && str2[jj] > '0'))
        {
            str3[ii+jj] = str2[jj];
        }
        
        jj++;
    }

    str3[ii+jj+1] = '\0';

    return str3;
}
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

#define LEN 100

LinkedList* readFile (char *fileName, FILE *file)
{
    char *temp;

    file = fopen(fileName, "r");
}
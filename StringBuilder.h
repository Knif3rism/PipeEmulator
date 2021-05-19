#include "FileIO.h"
#include "LinkedList.h"

LinkedList* stringBuilderToList (struct FileInformation file);
int wordCount(char* str);
char** splitString(char* string, int amt_space);
char* stringAppender(char* str1, char* str2);
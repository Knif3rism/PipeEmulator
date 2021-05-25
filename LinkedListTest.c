#include <stdio.h>
#include "LinkedList.h"

int main()
{
    LinkedList *list;

    Node_C *temp;

    list = newList();
    insertLast(list, (void*) "hello", 6);
    insertLast(list, (void*) "world!", 7);
    insertFirst(list, (void*) "From the top:", 15);

    temp = removeFirst(list);
    printf("%s ", (char*) temp->value);
    temp = removeFirst(list);
    printf("%s ", (char*) temp->value);
    temp = removeFirst(list);
    printf("%s ", (char*) temp->value);

    freeList(list);
}
/* name: Linked List with System Calls
 * author: Egan Chen
 * Date Created: 10/05/2021
 * Purpose: An implementation of a Linked List with no malloc
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "LinkedList.h"

#define PAGESIZE 4096


LinkedList* newList(int fileSize, char* fileName)
{
    struct LinkedList *newList;

    newList = mmap(NULL, sizeof(LinkedList*), PROT_READ | PROT_WRITE, MAP_SHARED, 0, 0);
    newList->head = NULL;
    newList->tail = NULL;
}

void insertFirst(LinkedList* list, char* string)
{
    struct Node *node;

    node = (void*) string;

    if (list->head == NULL)
    {
        node->next = NULL;
        node->prev = NULL;
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }

}

void insertLast(LinkedList* list, char* string)
{
    struct Node *node;

    node = (void*) string;

    if (list->tail == NULL)
    {
        node->next = NULL;
        node->prev = NULL;
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->next = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}

void* removeFirst(LinkedList* list)
{
    size_t size;
    int stat_status, mun_status;
    struct Node *outValue, *tempNode;

    outValue = list->head->value;
    tempNode = list->head;
    list->head = list->head->next;

    stat_status = stat(tempNode, size);
    
    if (stat_status != 0)
    {
        printf(stderr, "%s");
    }

    mun_status = munmap(tempNode, size);

    if (mun_status != 0)
    {
        printf(stderr, "%s");
    }

    return outValue;
}

void* removeLast(LinkedList* list)
{
    size_t size;
    int stat_status, mun_status;
    struct Node *outValue, *tempNode;

    outValue = list->tail->value;
    tempNode = list->tail;
    list->head = list->tail->prev;


    stat_status = stat(tempNode, size);
    
    if (stat_status != 0)
    {
        printf(stderr, "%s");
    }

    mun_status = munmap(tempNode, size);

    if (mun_status != 0)
    {
        printf(stderr, "%s");
    }


    return outValue;
}

int stringLength(char* string)
{
    int counter, ii;

    ii = 0;

    while (string[ii] != '\0')
    {
        counter++;
    }

    return counter;
}
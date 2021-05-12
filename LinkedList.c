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


LinkedList* newList()
{
    struct LinkedList *newList;

    newList = mmap(NULL, sizeof(LinkedList*), PROT_READ | PROT_WRITE, MAP_SHARED, 0, 0);
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}

void insertFirst(LinkedList* list, void* string, int str_Size)
{
    struct Node *node;

    node = mmap(NULL, sizeof(Node), 
                PROT_READ | PROT_WRITE, 
                MAP_SHARED, -1, 0);

    /*value reassignment might cause memory leak, be careful*/
    node->value = string;
    node->size = str_Size;

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

void insertLast(LinkedList* list, void* string, int str_Size)
{
    struct Node *node;

    node = mmap(NULL, sizeof(Node), 
                PROT_READ | PROT_WRITE, 
                MAP_SHARED, -1, 0);

    node->value = string;
    node->size = str_Size;

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


Node_C* removeFirst(LinkedList* list)
{
    int mun_status;
    struct Node *tempNode;
    struct Node_C *outValue;

    /* Obtain node*/
    outValue = list->head->value;
    tempNode = list->head;
    list->head = list->head->next;

    /*Prep string going out*/
    outValue = mmap(NULL, sizeof(Node_C),
                    PROT_READ | PROT_WRITE, 
                    MAP_SHARED, -1, 0);

    outValue->value = tempNode->value;
    outValue->size = tempNode->size;

    /* Free Memory */
    /*mun_status = munmap(tempNode->value, tempNode->size);*/
    mun_status = munmap(tempNode, sizeof(Node));
    if (mun_status != 0)
    {
        perror("unable to release memory");
    }

    return outValue;
}


Node_C* removeLast(LinkedList* list)
{
    int mun_status;
    struct Node *tempNode;
    struct Node_C *outValue;

    /* Get node */
    outValue = list->tail->value;
    tempNode = list->tail;
    list->head = list->tail->prev;

    /*Prep string going out*/
    outValue = mmap(NULL, sizeof(Node_C),
                    PROT_READ | PROT_WRITE, 
                    MAP_SHARED, -1, 0);

    outValue->value = tempNode->value;
    outValue->size = tempNode->size;

    /* Free Memory */
    mun_status = munmap(tempNode, sizeof(Node));
    if (mun_status != 0)
    {
        perror("unable to release memory");
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
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
#include <unistd.h>

#define PAGESIZE 4096
#define ERR_MSG_SIZE 256

LinkedList* newList()
{
    struct LinkedList *newList;

    newList = (LinkedList*) mmap(NULL, sizeof(LinkedList), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    newList->head = 0;
    newList->tail = 0;

    return newList;
}

void insertFirst(LinkedList* list, void* string, int str_Size)
{
    struct Node *node;

    node = mmap(NULL, sizeof(Node), 
                PROT_READ | PROT_WRITE, 
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    /*value reassignment might cause memory leak, be careful*/
    node->value = string;
    node->size = str_Size;

    if (list->head == NULL)
    {
        node->next = NULL;
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

    /*value reassignment might cause memory leak, be careful*/
    node = mmap(NULL, sizeof(Node), 
                PROT_READ | PROT_WRITE, 
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    node->value = string;
    node->size = str_Size;


    if (list->tail == NULL)
    {
        node->next = NULL;
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->prev = list->tail;
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
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    outValue->value = tempNode->value;
    outValue->size = tempNode->size;

    /* Free Memory */   
    mun_status = munmap(tempNode, sizeof(Node));
    if (mun_status != 0)
    {
        write(2, "unable to release memory", 25);
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
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    outValue->value = tempNode->value;
    outValue->size = tempNode->size;

    /* Free Memory */
    mun_status = munmap(tempNode, sizeof(Node));
    if (mun_status != 0)
    {
        write(2, "unable to release memory", 25);
    }

    return outValue;
}

void freeList(LinkedList* list)
{
    int mun_status;

    freeNode(list->head);
    mun_status = munmap(list, sizeof(LinkedList));

    if (mun_status != 0)
    {
        write(2, "unable to release memory", 25);
    }
}

void freeNode(Node* node)
{
    int mun_status;
    if ((node->next != NULL) || (node != NULL))
    {
        freeNode(node->next);

        mun_status = munmap(node->value, node->size);

        if (mun_status != 0)
        {
            write(2, "Unable to free node->value memory", 34);
        }

        mun_status = munmap(node, sizeof(Node));

        if (mun_status != 0)
        {
            write(2, "Unable to free node memory", ERR_MSG_SIZE);
        }
    }
}

int getSize(LinkedList *list)
{
    int count = 0;
    Node *curr = list->head;

    while(curr != NULL)
    {
        count++;
        curr = curr->next;
    }

    return count;
}

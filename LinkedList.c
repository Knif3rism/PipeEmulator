/* Name: Linked List void Edition
 * Author: Egan Chen
 * Date Created: 18/04/2021
 * Purpose: A general implementation of the linked list data structure using void pointers.
 */


#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"


LinkedList* newLinkedList()
{
    struct LinkedList *newList;

    newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}

void insertFirst(LinkedList* list, void* inValue)
{
    struct Node *node;

    /* Create a home for the node and set value to inValue */
    node = (Node*)malloc(sizeof(Node));
    node->value = inValue;

    /* If the list is empty then we make the new node point to nothing
     * because we assert that the list is empty because if head is NULL then tail is NULL
     */
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


void insertLast(LinkedList* list, void* inValue)
{
    struct Node *node;

    node = (Node*)malloc(sizeof(Node));
    node->value = inValue;

    /*if the tail is NULL we assert that the head is also NULL
     *as the only way for the list head to reach NULL is when it's empty
     */
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
    Node *tempNode;
    void *outValue;


    outValue = list->head->value;
    tempNode = list->head;
    list->head = list->head->next;
    free(tempNode);

    return outValue;
}

void* removeLast(LinkedList* list)
{

    Node *tempNode;
    void *outValue;


    outValue = list->tail->value;
    tempNode = list->tail;
    list->head = list->tail->prev;
    free(tempNode);

    return outValue;
}

/* Freeing Memory */
void freeList(LinkedList* list)
{
    freeNode(list->head);
    printf("\nhello2\n");
    free(list);
}

void freeNode(Node* node)
{
    if (node->next != NULL)
    {
        freeNode(node->next);
    }
    else
    {
        printf("\nhello\n");
        free(node->value);
        free(node);
    }
}
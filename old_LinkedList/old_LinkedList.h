#ifndef ListDefinition
#define ListDefinition

typedef struct Node
    {
        void* value;
        struct Node *next, *prev;
    }Node;

typedef struct LinkedList
    {
        Node* head;
        Node* tail;
    }LinkedList;

#endif

/* Tools */
int getSize(LinkedList* list);


LinkedList* newLinkedList();
void insertFirst(LinkedList* list, void* value);
void insertLast(LinkedList* list, void* value);
void* removeFirst(LinkedList* list);
void* removeLast(LinkedList* list);

/* Freeing Memory */
void freeList(LinkedList* list);
void freeNode(Node* node);

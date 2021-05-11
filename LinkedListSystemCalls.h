#ifndef ListSystemCalls
#define ListSystemCalls

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

LinkedList* newList(int fileSize, char* fileName);
void insertFirst(LinkedList* list, void* value);
void insertLast(LinkedList* list, void* value);
void* removeFirst(LinkedList* list);
void* removeLast(LinkedList* list);

void freeList(LinkedList* list);
void freeNode(Node* node);
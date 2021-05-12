#ifndef ListSystemCalls
#define ListSystemCalls

typedef struct Node
    {
        int size;
        void *value;
        struct Node *next, *prev;
    }Node;

typedef struct Node_C
    {
        int size;
        void *value;
    }Node_C;

typedef struct LinkedList
    {
        Node* head;
        Node* tail;
    }LinkedList;

#endif

LinkedList* newList();
void insertFirst(LinkedList* list, void* value, int str_Size);
void insertLast(LinkedList* list, void* value, int str_Size);
Node_C* removeFirst(LinkedList* list);
Node_C* removeLast(LinkedList* list);

void freeList(LinkedList* list);
void freeNode(Node* node);

int stringLength(char* string);
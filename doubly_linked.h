#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct Node
{
   struct Node *next;
   struct Node *prev;
   char *data;
};

struct List
{
   struct Node *head;
   struct Node *tail;
   int length;
};

int updateListLength(struct List *list);
int updateListLengthRecurse(struct Node *head, int currCount, int length);

void createDoubleList();
void traverseForward(struct List *list);
void deleteNodeAtHead(struct List *list);
void deleteNodeAtTail(struct List *list);
void insertNodeAtTail(struct List *list, char *data);
void insertNodeAtHead(struct List *list, char *data);
void deleteNodeAtPosition(struct List *list, int position);
void insertNodeAtPosition(struct List *list, char *data, int position);
void traverseForwardRecursively(struct Node *head);

struct Node *createNode(char *data);
struct Node *findInList(struct List *list, char *data);
struct Node *findNodeByPosition(struct List *list, int position);
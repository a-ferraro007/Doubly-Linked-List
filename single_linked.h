#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct SingleNode
{
   struct SingleNode *next;
   char *data;
};

struct SingleList
{
   struct SingleNode *head;
   struct SingleNode *tail;
   int length;
};

int updateListLengthSingle(struct SingleList *list);
int updateListLengthRecursivelySingle(struct SingleNode *head, int currCount, int length);

void createSingleList();
void traverseForwardSingle(struct SingleList *list);
void deleteNodeAtHeadSingle(struct SingleList *list);
void deleteNodeAtTailSingle(struct SingleList *list);
void insertNodeAtTailSingle(struct SingleList *list, char *data);
void insertNodeAtHeadSingle(struct SingleList *list, char *data);
void deleteNodeAtPositionSingle(struct SingleList *list, int position);
void insertNodeAtPositionSingle(struct SingleList *list, char *data, int position);
void traverseForwardRecursivelySingle(struct SingleNode *head);

struct SingleNode *createNodeSingle(char *data);
struct SingleNode *findInListSingle(struct SingleList *list, char *data);
struct SingleNode *findNodeByPositionSingle(struct SingleList *list, int position);
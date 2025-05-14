#include "stdio.h"
#include "stdlib.h"

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

struct Node *createNode(char *data)
{
   struct Node *node = (struct Node *)malloc(sizeof(struct Node));
   node->data = data;
   node->next = NULL;
   node->prev = NULL;

   return node;
}

void traverseForwardRecursively(struct Node *head)
{
   struct Node *curr = head;
   if (curr == NULL)
      return;
   printf("Data: %s\n", curr->data);
   traverseForwardRecursively(curr->next);
}

void traverseForward(struct List *list)
{
   struct Node *curr = list->head;
   while (curr != NULL)
   {
      printf("Data: %s\n", curr->data);
      curr = curr->next;
   }
}

struct Node *findInList(struct List *list, char *data)
{
   struct Node *curr = list->head;
   struct Node *node;

   while (curr != NULL)
   {
      if (curr->data == data)
      {
         node = curr;
         break;
      }
      curr = curr->next;
   }
   return node;
}

struct Node *findNodeByPosition(struct List *list, int position)
{
   int currPos = 0;
   struct Node *node;
   struct Node *curr = list->head;

   while (curr != NULL)
   {
      if (currPos == position)
      {
         node = curr;
         break;
      }
      currPos++;
      curr = curr->next;
   }
   return node;
}

int updateLengthOfList(struct List *list)
{
   int count = 0;
   struct Node *curr = list->head;
   while (curr != NULL)
   {
      count++;
      curr = curr->next;
   }
   list->length = count;
   return list->length;
}

int updateLengthOfListRecurse(struct Node *head, int currCount, int length)
{
   int count = currCount;
   struct Node *curr = head;

   if (curr == NULL)
   {
      length = count;
      return count;
   }

   count++;
   return updateLengthOfListRecurse(curr->next, count, length);
}

void insertNodeAtTail(struct List *list, char *data)
{
   printf("insertNodeAtTail\n");
   struct Node *newNode = createNode(data);
   if (list->head == NULL)
   {
      list->head = newNode;
      list->head->next = list->tail;
      if (list->tail != NULL)
         list->tail->prev = list->head;
   }
   else if (list->tail == NULL)
   {
      list->tail = newNode;
      list->tail->prev = list->head;
      list->head->next = list->tail;
   }
   else
   {
      struct Node *temp = list->tail;
      list->tail = newNode;
      temp->next = list->tail;
   }
   list->length++;
}

void insertNodeAtHead(struct List *list, char *data)
{
   printf("insertNodeAtHead\n");
   struct Node *newNode = createNode(data);
   if (list->head == NULL)
   {
      list->head = newNode;
      list->head->next = list->tail;
      if (list->tail != NULL)
         list->tail->prev = list->head;
   }
   else
   {
      struct Node *tmp = list->head;
      list->head = newNode;
      tmp->prev = list->head;
      list->head->next = tmp;
      if (list->tail == NULL)
         list->tail = tmp;
   }
   list->length++;
}

void insertNodeAtPosition(struct List *list, char *data, int position)
{
   printf("insertNodeAtPosition: %d\n", position);
   if (position <= list->length)
   {
      if (position == 0)
         insertNodeAtHead(list, data);
      else if (position == list->length - 1)
         insertNodeAtTail(list, data);
      else
      {
         struct Node *node = findNodeByPosition(list, position);
         if (node != NULL)
         {
            struct Node *newNode = createNode(data);
            newNode->prev = node->prev;
            newNode->next = node;
            node->prev = newNode;
            if (newNode->prev != NULL)
               newNode->prev->next = newNode;
            list->length++;
         }
         else
            printf("Error: Unable to find node at position: %d\n", position);
      }
   }
   else
      printf("Error: Insert position out of bounds\n");
}

void deleteNodeAtHead(struct List *list)
{
   printf("deleteNodeAtHead\n");
   if (list->head != NULL)
   {
      if (list->head->next == NULL)
      {
         list->head = NULL;
         list->length--;
         return;
      }

      struct Node *tmp = list->head->next;
      list->head = tmp;
      list->head->prev = NULL;
      list->head->next = tmp->next;
      tmp = NULL;
      list->length--;
   }
   else
      printf("Error: null head node\n");
}

void deleteNodeAtTail(struct List *list)
{
   printf("deleteNodeAtTail\n");
   if (list->tail != NULL)
   {
      if (list->tail == list->head)
      {
         list->tail = NULL;
         list->head = NULL;
         list->length--;
         return;
      }

      struct Node *tmp = list->tail->prev;
      list->tail = tmp;
      list->tail->next = NULL;
      list->tail->prev = tmp->prev;

      tmp = NULL;
      list->length--;
   }
   else
      printf("Error: null tail node\n");
}

void deleteNodeAtPosition(struct List *list, int position)
{
   printf("deleteNodeAtPosition: %d\n", position);
   if (position <= list->length)
   {
      if (position == 0)
         deleteNodeAtHead(list);
      else if (position == list->length - 1)
         deleteNodeAtTail(list);
      else
      {
         struct Node *node = findNodeByPosition(list, position);
         if (node != NULL)
         {
            struct Node *tmp = node;
            if (tmp->prev != NULL && tmp->prev->next != NULL)
               tmp->prev->next = node->next;
            if (tmp->next != NULL && tmp->next->prev != NULL)
               tmp->next->prev = node->prev;
            node = NULL;
            tmp = NULL;
            list->length--;
         }
         else
            printf("Error: Unable to find node at position: %d\n", position);
      }
   }
   else
      printf("Error: Delete position out of bounds\n");
}

int main()
{
   struct List *list = (struct List *)malloc(sizeof(struct List));
   list->length = 0;

   return 0;
}

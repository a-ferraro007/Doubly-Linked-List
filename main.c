#include "stdio.h"
#include "stdlib.h"
#include "string.h"
const char *COMMANDS = "COMMANDS\n - insert head <data>\n - insert tail <data>\n - insert <position> <data>\n - delete <position>\n - delete head\n - delete tail\n - print\n - print head\n - print tail\n - length\n - exit\n type 'help' to see this list again\n";

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
   node->data = malloc(strlen(data) + 1);
   strcpy(node->data, data);
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

int updateListLength(struct List *list)
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

int updateListLengthRecurse(struct Node *head, int currCount, int length)
{
   int count = currCount;
   struct Node *curr = head;

   if (curr == NULL)
   {
      length = count;
      return count;
   }

   count++;
   return updateListLengthRecurse(curr->next, count, length);
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
   if (list->head != NULL)
      printf("insertNodeAtHead: %s\n", list->head->data);

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
      printf("node tmp: %s\nnode head: %s\n", tmp->data, list->head->data);
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
         free(list->head->data);
         free(list->head);
         list->head = NULL;
         list->length--;
         return;
      }

      struct Node *tmp = list->head;
      list->head = tmp->next;
      list->head->prev = NULL;
      if (tmp->next->next != NULL)
         list->head->next = tmp->next->next;
      free(tmp->data);
      free(tmp);
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

         free(list->head->data);
         free(list->tail->data);
         free(list->head);
         free(list->tail);
         list->tail = NULL;
         list->head = NULL;
         list->length--;
         return;
      }

      struct Node *tmp = list->tail;
      list->tail = tmp->prev;
      list->tail->next = NULL;
      if (tmp->prev != NULL)
         list->tail->prev = tmp->prev->prev;

      free(tmp->data);
      free(tmp);
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

            free(tmp->data);
            free(tmp);
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

int main(int argc, const char **argv)
{
   char input[1024];
   struct List *list = (struct List *)malloc(sizeof(struct List));
   list->length = 0;

   printf("Create a doubly linked list\n\n");
   printf("%s", COMMANDS);

   while (strcmp(input, "exit") != 0)
   {
      printf("> ");
      fgets(input, BUFSIZ, stdin);
      input[strcspn(input, "\n")] = '\0';
      char *cmd = strtok(input, " ");

      if (strcmp(cmd, "insert") == 0)
      {
         char *arg = strtok(NULL, " ");
         char *end;
         long int pos = strtol(arg, &end, 10);

         if (strcmp(arg, "head") == 0)
         {
            char *data = strtok(NULL, " ");
            printf("inserting data: %s at head\n", data);
            insertNodeAtHead(list, data);
         }
         else if (strcmp(arg, "tail") == 0)
         {
            char *data = strtok(NULL, " ");
            printf("inserting data: %s at tail\n", data);
            insertNodeAtTail(list, data);
         }
         else if (arg != end)
         {
            char *data = strtok(NULL, " ");

            printf("inserting data: %s at position %ld\n", data, pos);
            insertNodeAtPosition(list, data, pos);
         }
         else
         {
            printf("invalid insert command\n");
         }
      }

      else if (strcmp(cmd, "delete") == 0)
      {
         char *arg = strtok(NULL, " ");
         char *end;
         long int pos = strtol(arg, &end, 10);

         if (strcmp(arg, "head") == 0)
         {
            printf("delete head node\n");
            deleteNodeAtHead(list);
         }
         else if (strcmp(arg, "tail") == 0)
         {
            printf("delete tail node\n");
            deleteNodeAtTail(list);
         }
         else if (arg != end)
         {
            printf("delete node at position %ld\n", pos);
            deleteNodeAtPosition(list, pos);
         }
         else
         {
            printf("invalid delete command\n");
         }
      }
      else if (strcmp(cmd, "print") == 0)
      {
         char *arg = strtok(NULL, " ");

         if (arg == NULL)
         {
            traverseForward(list);
         }
         else if (strcmp(arg, "head") == 0)
         {
            if (list->head != NULL)
               printf("Head node: %s\n", list->head->data);
            else
               printf("Head node: NULL");
         }
         else if (strcmp(arg, "tail") == 0)
         {
            if (list->tail != NULL)
               printf("Tail node: %s\n", list->tail->data);
            else
               printf("Tail node: NULL");
         }
      }
      else if (strcmp(cmd, "length") == 0)
      {
         printf("List Length: %d\n", list->length);
      }
      else if (strcmp(cmd, "help") == 0)
      {
         printf("%s", COMMANDS);
      }
      else
      {
         printf("command not found\n");
      }
   }
   printf("Exiting...");
   return 0;
}
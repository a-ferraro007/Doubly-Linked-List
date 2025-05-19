#include "doubly_linked.h"

const char *COMMANDS__ = "COMMANDS\n - insert head <data>\n - insert tail <data>\n - insert <position> <data>\n - delete <position>\n - delete head\n - delete tail\n - print\n - print head\n - print tail\n - length\n - exit\n type 'help' to see this list again\n";

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

void print(struct Node *node, struct Node *head, struct Node *tail)
{
   if (node == NULL)
      return;

   if (node == head)
   {
      printf("%s", node->data);

      if (node->next != NULL)
      {
         printf(" -> ");
      }
   }
   else if (node == tail)
   {
      if (node->prev != NULL)
      {
         printf("<- ");
      }
      printf("%s", node->data);
      ;
   }
   else
   {
      if (node->prev != NULL)
      {
         printf("<- ");
      }
      printf("%s", node->data);

      if (node->next)
      {
         printf(" -> ");
      }
   }
}

void traverseForward(struct List *list)
{
   struct Node *curr = list->head;
   while (curr != NULL)
   {
      print(curr, list->head, list->tail);
      curr = curr->next;
   }
   printf("\n");
}

struct Node *findInList(struct List *list, char *data)
{
   struct Node *curr = list->head;
   struct Node *node = NULL;

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
   struct Node *node = NULL;
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
      list->length++;
   }
   else if (list->tail == NULL)
   {
      list->tail = newNode;
      list->tail->prev = list->head;
      list->head->next = list->tail;
      list->length++;
   }
   else
   {
      struct Node *tmp = list->tail;
      newNode->prev = tmp;
      list->tail = newNode;
      tmp->next = list->tail;
      list->length++;
   }
}

void insertNodeAtHead(struct List *list, char *data)
{
   printf("insertNodeAtHead: %s\n", data);
   struct Node *newNode = createNode(data);
   if (list->head == NULL)
   {
      list->head = newNode;
      list->head->next = list->tail;
      list->tail = newNode;
      if (list->tail != NULL)
         list->tail->prev = list->head;
      list->length++;
      return;
   }

   struct Node *tmp = list->head;
   list->head = newNode;
   tmp->prev = list->head;
   list->head->next = tmp;
   if (list->tail == NULL)
      list->tail = tmp;
   list->length++;
}

void insertNodeAtPosition(struct List *list, char *data, int pos)
{
   printf("insertNodeAtPosition: %d\n", pos);
   if (pos <= list->length && pos > 0)
   {
      if (pos == 1)
         insertNodeAtHead(list, data);
      else if (pos == list->length)
         insertNodeAtTail(list, data);
      else
      {
         struct Node *node = findNodeByPosition(list, pos - 1);
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
            printf("Error: Unable to find node at position: %d\n", pos);
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
      printf("Error: empty list\n");
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
      if (tmp->prev != NULL)
         list->tail->prev = tmp->prev->prev;

      free(list->tail->next->data);
      free(list->tail->next);
      list->tail->next = NULL;
      // tmp = NULL;
      list->length--;
   }
   else
      printf("Error: empty list\n");
}

void deleteNodeAtPosition(struct List *list, int pos)
{
   printf("deleteNodeAtPosition: %d\n", pos);
   if (pos <= list->length)
   {
      if (pos == 0)
         deleteNodeAtHead(list);
      else if (pos == list->length - 1)
         deleteNodeAtTail(list);
      else
      {
         struct Node *node = findNodeByPosition(list, pos);
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
            printf("Error: Unable to find node at position: %d\n", pos);
      }
   }
   else
      printf("Error: Delete position out of bounds\n");
}

void createDoubleList()
{
   char cmdInput[1024];
   struct List *list = (struct List *)malloc(sizeof(struct List));

   while (strcmp(cmdInput, "exit") != 0)
   {
      printf("> ");
      fgets(cmdInput, BUFSIZ, stdin);
      cmdInput[strcspn(cmdInput, "\n")] = '\0';
      char *cmd = strtok(cmdInput, " ");

      if (strcmp(cmd, "insert") == 0)
      {
         char *arg = strtok(NULL, " ");
         char *end;
         long int pos = strtol(arg, &end, 10);

         if (strcmp(arg, "head") == 0)
         {
            char *data = strtok(NULL, " ");
            if (data != NULL)
            {
               printf("inserting data: %s at head\n", data);
               insertNodeAtHead(list, data);
            }
            else
               printf("Error: invalid insert command\n");
         }
         else if (strcmp(arg, "tail") == 0)
         {
            char *data = strtok(NULL, " ");
            if (data != NULL)
            {
               printf("inserting data: %s at tail\n", data);
               insertNodeAtTail(list, data);
            }
            else
               printf("Error: invalid insert command\n");
         }
         else if (arg != end)
         {
            char *data = strtok(NULL, " ");
            if (data != NULL && pos >= 0)
            {
               printf("inserting data: %s at position %ld\n", data, pos);
               insertNodeAtPosition(list, data, pos);
            }
            else
               printf("Error: invalid insert command\n");
         }
         else
            printf("Error: invalid insert command\n");
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
               printf("Head node: NULL\n");
         }
         else if (strcmp(arg, "tail") == 0)
         {
            if (list->tail != NULL)
               printf("Tail node: %s\n", list->tail->data);
            else
               printf("Tail node: NULL\n");
         }
      }
      else if (strcmp(cmd, "length") == 0)
      {
         printf("List Length: %d\n", list->length);
      }
      else if (strcmp(cmd, "help") == 0)
      {
         printf("\n%s", COMMANDS__);
      }
      else
      {
         printf("command not found\n");
      }
   }
}
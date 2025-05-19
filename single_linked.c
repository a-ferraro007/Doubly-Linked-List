#include "single_linked.h"

const char *__COMMANDS__ = "COMMANDS\n - insert head <data>\n - insert tail <data>\n - insert <position> <data>\n - delete <position>\n - delete head\n - delete tail\n - print\n - print head\n - print tail\n - length\n - exit\n type 'help' to see this list again\n";

struct SingleNode *createNodeSingle(char *data)
{
   struct SingleNode *node = (struct SingleNode *)malloc(sizeof(struct SingleNode));
   node->data = malloc(strlen(data) + 1);
   strcpy(node->data, data);
   node->next = NULL;

   return node;
}

int updateListLengthSingle(struct SingleList *list)
{
   int count = 0;
   struct SingleNode *curr = list->head;
   while (curr != NULL)
   {
      count++;
      curr = curr->next;
   }
   list->length = count;
   return list->length;
}

int updateListLengthRecursivelySingle(struct SingleNode *head, int currCount, int length)
{
   int count = currCount;
   struct SingleNode *curr = head;

   if (curr == NULL)
   {
      length = count;
      return count;
   }

   count++;
   return updateListLengthRecursivelySingle(curr->next, count, length);
}

void traverseForwardRecursivelySingle(struct SingleNode *head)
{
   struct SingleNode *curr = head;
   if (curr == NULL)
      return;
   printf("Data: %s\n", curr->data);
   traverseForwardRecursivelySingle(curr->next);
}

void printSingle(struct SingleNode *node, struct SingleNode *head, struct SingleNode *tail)
{
   if (node == NULL)
      return;

   printf("%s", node->data);

   if (node->next != NULL)
   {
      printf(" -> ");
   }
}

void traverseForwardSingle(struct SingleList *list)
{
   struct SingleNode *curr = list->head;
   while (curr != NULL)
   {
      printSingle(curr, list->head, list->tail);
      curr = curr->next;
   }
   printf("\n");
}

struct SingleNode *findInListSingle(struct SingleList *list, char *data)
{
   struct SingleNode *curr = list->head;
   struct SingleNode *node = NULL;

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

struct SingleNode *findNodeByPositionSingle(struct SingleList *list, int position)
{
   int currPos = 1;
   struct SingleNode *node = NULL;
   struct SingleNode *curr = list->head;

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

void insertNodeAtHeadSingle(struct SingleList *list, char *data)
{
   printf("insertNodeAtHead\n");
   struct SingleNode *node = createNodeSingle(data);
   if (list->head == NULL)
   {
      list->head = node;
      list->tail = node;
      list->length++;
      return;
   }
   struct SingleNode *tmp = list->head;
   node->next = tmp;
   list->head = node;
   list->length++;
}

void insertNodeAtTailSingle(struct SingleList *list, char *data)
{

   struct SingleNode *node = createNodeSingle(data);
   if (list->tail == NULL && list->head == NULL)
   {
      printf("insertNodeAtTail->");
      insertNodeAtHeadSingle(list, data);
      return;
   }

   printf("insertNodeAtTail\n");
   struct SingleNode *tmp = list->tail;
   list->tail = node;
   tmp->next = list->tail;
   list->length++;
}

void insertNodeAtPositionSingle(struct SingleList *list, char *data, int pos)
{
   if (pos > 0 && pos <= list->length + 1)
   {
      if (pos == 1)
         insertNodeAtHeadSingle(list, data);
      else if (pos == list->length + 1)
         insertNodeAtTailSingle(list, data);
      else
      {
         struct SingleNode *node = findNodeByPositionSingle(list, pos - 1);
         if (node != NULL)
         {
            struct SingleNode *newNode = createNodeSingle(data);
            struct SingleNode *tmp = node->next;
            node->next = newNode;
            newNode->next = tmp;
            list->length++;
         }
         else
            printf("Error: Unable to find node at position: %d\n", pos);
      }
   }
   else
      printf("Error: Insert position out of bounds\n");
}

void deleteNodeAtHeadSingle(struct SingleList *list)
{
   if (list->head != NULL)
   {
      struct SingleNode *tmp = list->head;
      list->head = tmp->next;
      free(tmp->data);
      free(tmp);
      tmp = NULL;
      list->length--;
   }
   else
      printf("Error: null head node\n");
}

void deleteNodeAtTailSingle(struct SingleList *list)
{
   if (list->length > 0)
   {
      if (list->length == 1)
      {
         list->head = NULL;
         list->tail = NULL;
         free(list->head->data);
         free(list->head);
         free(list->tail->data);
         free(list->tail);
         list->length--;
      }
      else
      {
         struct SingleNode *node = findNodeByPositionSingle(list, list->length - 1);
         if (node != NULL)
         {
            list->tail = node;
            free(node->next->data);
            free(node->next);
            node->next = NULL;
            list->length--;
         }
         else
            printf("Error: Unable to find tail node");
      }
   }
   else
      printf("Error: list is empty\n");
}

void deleteNodeAtPositionSingle(struct SingleList *list, int position)
{
   printf("deleteNodeAtPosition: %d\n", position);
   if (position <= list->length)
   {
      if (position == 1)
         deleteNodeAtHeadSingle(list);
      else if (position == list->length)
         deleteNodeAtTailSingle(list);
      else
      {
         struct SingleNode *node = findNodeByPositionSingle(list, position - 1);
         if (node != NULL)
         {
            struct SingleNode *tmp = node->next;
            node->next = node->next->next;
            free(tmp->data);
            free(tmp);
            list->length--;
         }
         else
            printf("Error: Unable to find node at position: %d\n", position);
      }
   }
   else
      printf("Error: Delete position out of bounds\n");
}

void createSingleList()
{
   char cmdInput[1024];
   struct SingleList *list = (struct SingleList *)malloc(sizeof(struct SingleList));
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
               insertNodeAtHeadSingle(list, data);
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
               insertNodeAtTailSingle(list, data);
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
               insertNodeAtPositionSingle(list, data, pos);
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
            deleteNodeAtHeadSingle(list);
         }
         else if (strcmp(arg, "tail") == 0)
         {
            printf("delete tail node\n");
            deleteNodeAtHeadSingle(list);
         }
         else if (arg != end)
         {
            printf("delete node at position %ld\n", pos);

            deleteNodeAtPositionSingle(list, pos);
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
            traverseForwardSingle(list);
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
         printf("\n%s", __COMMANDS__);
      }
      else
      {
         printf("command not found\n");
      }
   }
}
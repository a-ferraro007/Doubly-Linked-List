#include "ctype.h"
#include "doubly_linked.h"
#include "single_linked.h"

const char *_COMMANDS_ = "COMMANDS\n - insert head <data>\n - insert tail <data>\n - insert <position> <data>\n - delete <position>\n - delete head\n - delete tail\n - print\n - print head\n - print tail\n - length\n - exit\n type 'help' to see this list again\n";

void toLowerCase(char *str)
{
   while (*str)
   {
      *str = tolower(*str);
      str++;
   }
}

int main(int argc, const char **argv)
{
   char listType[20];

   printf("Create A Linked List\n\n");
   printf("- single\n- double\n");
   printf("> ");
   fgets(listType, 20, stdin);
   toLowerCase(listType);

   listType[strcspn(listType, "\n")] = '\0';
   printf("\n%s", _COMMANDS_);

   if (strcmp(listType, "single") == 0)
      createSingleList();
   else if (strcmp(listType, "double") == 0)
      createDoubleList();
   else
      printf("Error: invalid list selection\n");

   printf("Exiting...");
   return 0;
}

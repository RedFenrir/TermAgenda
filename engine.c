/*
  TODO

      MINOR STUFF

      acceptable_date function
      menu
      fix display stuff
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_SZ 256

typedef struct _Node{
  char* TITLE;
  char* MESSAGE;
  char* DATE;
  struct _Node *next;
}Node;

bool acceptable_date(char *date){

  /*

    function that sees if a date is in correct date/time format

  */

  return true;

}

void print_list(Node *list){
  printf("DATE\t\t| TITLE\t\t| MESSAGE\t\t|\n");
  Node *ptr;
  for(ptr = list; ptr != NULL; ptr = ptr->next)
    printf("%s\t\t| %s\t\t| %s\t\t|\n", ptr->DATE, ptr->TITLE, ptr->MESSAGE);
  }
Node *add_listt(Node *list, char *date, char *title, char *message){

  printf("%s is the correct date", date);

  return list;
}
Node *add_list(Node *list, char *date, char *title, char *message){

  Node *ptr = (Node*) malloc(sizeof(Node));
  (*ptr).DATE = (char*) malloc(sizeof(char)*strlen(date));
  ptr->TITLE = (char*) malloc(sizeof(char)*strlen(title));
  ptr->MESSAGE = (char*) malloc(sizeof(char)*strlen(message));

  strcpy(ptr->DATE,date);
  strcpy(ptr->TITLE,title);
  strcpy(ptr->MESSAGE,message);

  ptr->next = list;

  return ptr;
}

void free_list(Node *list){
  if(list->next != 0)
    free_list(list->next);
  else  free(list);
}


Node *add_event(Node *list){
  char *message_ = malloc(MAX_NAME_SZ);
    if(message_ == NULL){
        printf("ERROR - No memory for message variable\n");
        return NULL;
    }
  char *title_ = malloc(MAX_NAME_SZ-200);
      if(title_ == NULL){
          printf("ERROR - No memory for title variable\n");
          return NULL;
      }
  char date[11];

  printf("Date: ");
  scanf(" %s", &date);

  printf("Title: ");
  scanf(" %[^\n]s", title_);
  if ((strlen(title_) > 0) && (title_[strlen (title_) - 1] == '\n'))
      title_[strlen (title_) - 1] = '\0';

  printf("Message: ");
  scanf(" %[^\n]s", message_);
  if ((strlen(message_) > 0) && (message_[strlen (message_) - 1] == '\n'))
      message_[strlen (message_) - 1] = '\0';


  printf("Data gained correctly..\n");

  list = add_list(list, date, title_, message_);

  printf("\nOK, stored...\nPrinting complete agenda...\n");
  print_list(list);

  return list;
}

Node *read_file(){

  FILE *fp;
  char *path = (char*) malloc(sizeof(char)*256);
  char *str = (char*) malloc(sizeof(char)*300);
  Node *ptr;
  char date[10];
  char title[56];
  char message[256];
  char *DATE = (char*) malloc(sizeof(char)*strlen(date));
  char *TITLE = (char*) malloc(sizeof(char)*strlen(title));
  char *MESSAGE = (char*) malloc(sizeof(char)*strlen(message));

  ptr = NULL;
  printf("Enter file's path: ");
  scanf(" %[^\n]s", path);

  if((fp = fopen(path, "r")) == NULL){
    printf("Error - File doesn't exist");
    return NULL;
  }

  int count = 0;
  while (fscanf(fp, "%s", str)!=EOF){
    count++;
        
    switch (count){
      case 1:
        strcpy(date, str);
        break;
      case 2:
        strcpy(title, str);
        break;
      case 3:
        strcpy(message, str);
        break;
    }

    if(count == 3){
      DATE = realloc(DATE, 10);
      TITLE = realloc(TITLE, 56);
      MESSAGE = realloc(MESSAGE, 256);

      strcpy(DATE,date);
      strcpy(TITLE,title);
      strcpy(MESSAGE,message);

      ptr = add_list(ptr, DATE, TITLE, MESSAGE);
      count = 0;
    }
  }
  fclose(fp);
  fp = fopen(path, "w");
  printf("done reading...\n");
  print_list(ptr);

  fclose(fp);

  return ptr;
}


void saving_results(Node *list){

  FILE *fp;
  char choice = '\0';
  char *path = (char*) malloc(sizeof(char)*256);
  if(path == NULL){
      printf("ERROR - No memory for path variable\n");
  }

  printf("Enter file path, please: ");
  scanf(" %[^\n]s", path);
  printf("Are you sure in opening this path -> \"%s\" ? [Y/N]: ", path);
  scanf(" %c", &choice);
  if(choice == 'n'){
    path = realloc(path, 256);
    printf("Enter file path, please: ");
    scanf(" %s", path);
    printf("Opening \"%s\" this path, right? [Y/N]: ");
    scanf(" %c", &choice);
  }

  if((fp = fopen(path, "a")) == NULL){
    printf("ERROR - File doesn't exist");
  }

  Node *ptr = NULL;
  for(ptr = list; ptr != NULL; ptr = (*ptr).next){
    fprintf(fp, "%s\t\t %s\t\t %s\t\t\n", ptr->DATE, ptr->TITLE, ptr->MESSAGE);
  }

  printf("File saved...\nFreeing memory...\nClosing...\n");

}

int main(int argc, char **argv){

 printf("adding new stuff\n");
  Node *ptr;
  char choice = '\0';

  ptr = NULL;

  printf("Do you want to read an existing file? [Y/N]: ");
  scanf(" %c", &choice);
  if(choice == 'Y' || choice == 'y'){
    printf("Reading file...\n");
    ptr = read_file();
  }

  printf("\nDo you want to add an event? [Y/N]: ");
  scanf(" %c", &choice);
  while(choice == 'Y' || choice == 'y'){
    ptr = add_event(ptr);
    printf("\nDo you want to add a new event? [Y/N]: ");
    scanf(" %c", &choice);
  }

  printf("\nDo you want to save the result? [Y/N]: ");
  scanf(" %c", &choice);
  if(choice == 'Y' || choice == 'y'){
    saving_results(ptr);
  }

  free_list(ptr);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _Option{
  char* name;
  int id;
  bool pressed;
}Option;

typedef struct _Node{
  Option *opt;
  struct _Node *next;
}Node;

int counting_nodes(Node *list){
  if(list == NULL)
    return 0;

  else  return 1 + counting_nodes(list->next);
}

Node* add_list(Node *list, Option *option){

  Node *ptr = (Node*) malloc(sizeof(Node));

  ptr->opt =  option;
  ptr->next = list;

  return ptr;
}

Node *bottom(Node *list, Option *option){
  Node *ptr;
  if(list == NULL){
    ptr = add_list(ptr, option);
    ptr->next = NULL;
  }

  else{
    list->next = bottom(list->next, option);

    return list;
  }
}

Option* define_option(char* opt_name, int opt_id){

  Option *opt = (Option*) malloc(sizeof(Option));
  opt->name = (char*) malloc(sizeof(char)*strlen(opt_name));

  strcpy(opt->name, opt_name);
  opt->pressed = false;
  opt->id = opt_id;

  return opt;
}

bool check_order(Node *list){

  Node *ptr;
  bool ordered = true;
  int counter_ordering = 0;

  counter_ordering = list->opt->id;

  for(ptr = list->next; ptr != NULL; ptr = ptr->next){
    counter_ordering--;
    if(ptr->opt->id != counter_ordering)
      ordered = false;
  }

  return ordered;
}

void print_list(Node *ptr){
  Node *p;
  int counter = 1;

  for(p = ptr; p != NULL; p = p->next){
    printf("%d", p->opt->id);
    printf(" %s\n", p->opt->name);
    counter++;
  }
}


int handle_list(Node *ptr){

  if(check_order(ptr) == false){
    printf("ERROR - wrong id order\n");
    return 0;
  }
  else
    printf("[j] - Ordered\n\n");

  Node *p;
  int counter = 0;
  int id_counter = 0;
  int h_top = 0;
  int returning = 0;
  int current_value = 0;
  char c = '\0';

  for(p = ptr; p != NULL; p = p->next)
    if(p->next == NULL)
      h_top = p->opt->id;

  Option *h = NULL;

  for(p = ptr; p != NULL; p = p->next)
    printf("%s\n", p->opt->name);
  printf("\n");

  h = define_option("exit", h_top-1);
  ptr = bottom(ptr, h);

  print_list(ptr);

  do{
    printf("MENU\n\n---------------------------\n\n");
    for(p = ptr; p != NULL; p = p->next){
      if(p->opt->id == current_value){
        printf("[*] %s [*]\n", p->opt->name);
        p->opt->pressed = true;
      }
      else
        printf("    %s\n", p->opt->name);
    }
    system ("/bin/stty raw");
    while((c=getchar())!= '.') {
      /* type a period to break out of the loop, since CTRL-D won't work raw */
      putchar(c);
    }
    /* use system call to set terminal behaviour to more normal behaviour */
    system ("/bin/stty cooked");
    returning = current_value;
  }while(c == 13);

  return returning;;
}


int main(int argc, char **argv){

  Option *h1, *h2, *h3;
  Node *ptr;

  h1 = NULL;
  h1 = NULL;
  h3 = NULL;
  ptr = NULL;

  h1 = define_option("hello", 1);
  h2 = define_option("world", 2);
  h3 = define_option("C", 3);

  ptr = add_list(ptr, h1);
  ptr = add_list(ptr, h2);
  ptr = add_list(ptr, h3);

  int h = handle_list(ptr);

  return 0;
}

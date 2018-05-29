#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

Node* add_list(Node *list, Option *opt){

  Node *ptr = (Node*) malloc(sizeof(Node));
  ptr->opt =  opt;
  ptr->next = list;

  return ptr;
}

Option* define_option(Option *opt, char *opt_name, int opt_id){

  opt = (Option*) malloc(sizeof(Option));
  opt->name = opt_name;
  opt->pressed = false;
  opt->id = opt_id;

  return opt;
}

bool check_order(Node *list){

  Node *ptr;
  bool ordered = true;
  int counter_ordering = 0;

  counter_ordering = list->opt->id;

  for(ptr->next = list; ptr != NULL; ptr = ptr->next){
      if(ptr->opt->id != ++counter_ordering)
        ordered = false;
  }

  return ordered;
}

int handle_list(Node *ptr, int initial_value){
  Node *p;
  int counter = 0;
  int id_counter = 0;

  if(check_order(ptr) == false){
    printf("ERROR - wrong id order\n");
    return 0;  
  }

  for(p = ptr; p != NULL; p = p->next)
    if(initial_value == p->opt->id)
      counter++;
  if(counter == 0)
    printf("ERROR - in handling initial value");
    return 0;

  for(p = ptr; p != NULL; p = p->next){
    if(p->opt->id == initial_value){
      printf("[*] %s [*]\n", p->opt->name);
      p->opt->pressed = true;
    }
    else
      printf("    %s", p->opt->name);
  }

  return id_counter;
}


int main(int argc, char **argv){
  Option *h1, *h2, *h3;
  Node *ptr;

  h1 = NULL;
  h1 = NULL;
  h3 = NULL;
  ptr = NULL;

  h1 = define_option(h1, "hello", 1);
  h2 = define_option(h2, "world", 2);
  h3 = define_option(h3, "C", 3);

  ptr = add_list(ptr, h1);
  ptr = add_list(ptr, h2);
  ptr = add_list(ptr, h3);

  int h = handle_list(ptr, 1);

  return 0;
}

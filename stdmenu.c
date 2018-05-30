#include "stdmenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

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

int find_max(Node *list, int value){
  if(list->next == NULL){
    if(list->opt->id >= value)
      return list->opt->id;
    else  return value;
  }

  if(list->opt->id >= value)
    value = list->opt->id;

  return find_max(list->next, value);
}

int find_min(Node *list, int value){
  if(list->next == NULL){
    if(list->opt->id <= value)
      return list->opt->id;
    else  return value;
  }

  if(list->opt->id <= value)
    value = list->opt->id;

  return find_min(list->next, value);
}


int handle_list(Node *ptr){

  if(check_order(ptr) == false){
    printf("ERROR - wrong id order\n");
    return 0;
  }
  else
    printf("[j] - Ordered\n\n");

  Node *p;
  Node *curr;
  int counter = 0;
  int id_counter = 0;
  int h_top = 0;
  int current_value = 0;
  char c = '\0';
  bool flag = false;
  bool pressed = false;

  for(p = ptr; p != NULL; p = p->next)
    if(p->next == NULL)
      h_top = p->opt->id;

  Option *h = NULL;

  h = define_option("exit", h_top-1);
  ptr = bottom(ptr, h);

  do{
    system("clear");
    if(flag == true){
      printf("[j] - Invalid Enter\n");
      flag = false;
    }

    printf("MENU\n\n---------------------------\n\n");
    for(p = ptr; p != NULL; p = p->next){
      if(p->opt->id == current_value){
        printf("[*] %s [*]\n", p->opt->name);
        p->opt->pressed = true;
        curr = p;
      }
      else
        printf("    %s\n", p->opt->name);
    }
    printf(">");
    scanf(" %c", &c);
    if( c == 's'){
      curr->opt->pressed = false;
      if(current_value-1 >= (find_min(ptr, 0))){
        printf("[j] - ok, you can go up\n");
        current_value--;
      }
    }

    else if(c == 'w'){
      curr->opt->pressed = false;
      if(current_value+1 <= find_max(ptr, 0)){
        printf("[j] - ok, you can go down\n");
        current_value++;
      }
    }

    else if(c == 'k')
      pressed = true;

    else  flag = true;
  }while(pressed != true);


//TODO this is for input without enter
/*
  system ("/bin/stty raw");
  while((c=getchar())!= '.') {
    // type a period to break out of the loop, since CTRL-D won't work raw
    putchar(c);
  }
  // use system call to set terminal behaviour to more normal behaviour
  system ("/bin/stty cooked");
  }while(c == 13);
*/
  return current_value;
}

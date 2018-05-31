#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct _Option{
  char* name;
  int id;
  bool pressed;
}Option;

typedef struct _Nodel{
  Option *opt;
  struct _Nodel *next;
}Nodel;

int counting_Nodels(Nodel *list){
  if(list == NULL)
    return 0;

  else  return 1 + counting_Nodels(list->next);
}

Nodel* add(Nodel *list, Option *option){

  Nodel *ptr = (Nodel*) malloc(sizeof(Nodel));

  ptr->opt =  option;
  ptr->next = list;

  return ptr;
}

Nodel *bottom(Nodel *list, Option *option){
  Nodel *ptr;
  if(list == NULL){
    ptr = add(ptr, option);
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

bool check_order(Nodel *list){

  Nodel *ptr;
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

int find_max(Nodel *list, int value){
  if(list->next == NULL){
    if(list->opt->id >= value)
      return list->opt->id;
    else  return value;
  }

  if(list->opt->id >= value)
    value = list->opt->id;

  return find_max(list->next, value);
}

int find_min(Nodel *list, int value){
  if(list->next == NULL){
    if(list->opt->id <= value)
      return list->opt->id;
    else  return value;
  }

  if(list->opt->id <= value)
    value = list->opt->id;

  return find_min(list->next, value);
}


int handle_list(Nodel *ptr){

  if(check_order(ptr) == false){
    printf("ERROR - wrong id order\n");
    return 0;
  }
  else
    printf("[j] - Ordered\n\n");

  Nodel *p;
  Nodel *curr;
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

int main(int argc, char **argv){

  Option *h1, *h2, *h3, *h4;
  Nodel *list;
  h1 = NULL;
  h2 = NULL;
  h3 = NULL;
  h4 = NULL;
  list = NULL;

  h1 = define_option("Read a file", 4);
  h2 = define_option("Print Agenda", 3);
  h3 = define_option("Save a file", 2);
  h4 = define_option("Add an event", 1);

  list = add(list, h4);
  list = add(list, h3);
  list = add(list, h2);
  list = add(list, h1);

  int h = 1000;

  h = handle_list(list);
  system("clear");
  printf("%d", h);
  return 0;
}

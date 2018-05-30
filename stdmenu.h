#ifndef _STDMENU_H_
#define _STDMENU_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

//defining types

typedef struct _Option{
  char* name;
  int id;
  bool pressed;
}Option;

typedef struct _Nodel{
  Option *opt;
  struct _Nodel *next;
}Nodel;

//defining functions

Nodel* add(Nodel *list, Option *option);
Nodel *bottom(Nodel *list, Option *option);
Option* define_option(char* opt_name, int opt_id);
bool check_order(Nodel *list);
int counting_Nodels(Nodel *list);
int find_max(Nodel *list, int value);
int find_min(Nodel *list, int value);
int handle_list(Nodel *ptr);

#endif

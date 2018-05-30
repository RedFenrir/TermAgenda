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

typedef struct _Node{
  Option *opt;
  struct _Node *next;
}Node;

//defining functions

Node* add_list(Node *list, Option *option);
Node *bottom(Node *list, Option *option);
Option* define_option(char* opt_name, int opt_id);
bool check_order(Node *list);
void print_list(Node *ptr);
int counting_nodes(Node *list);
int find_max(Node *list, int value);
int find_min(Node *list, int value);
int handle_list(Node *ptr);

#endif

#ifndef _STDDATE_H_
#define _STDDATE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _Date{
  int start;
  int end;
}Date;

char *returning(int s, int e, char *string);
bool acceptable_date(char *date_time);

#endif

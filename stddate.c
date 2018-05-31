#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char *returning(int s, int e, char *string){

  char *new_string = (char*) malloc(sizeof(char*)*(e-s));
  int i = 0;

  for(i = 0; i < (e-s); i++)
    new_string[i] = string[s+i];

  printf("\n%s\n", new_string);
  return new_string;
}

bool acceptable_date(char *date_time){
  int counter = 0;
  int str = 0;
  int end = 0;
  bool flag = false;
  bool acceptable = true;

  char *day = (char*) malloc(sizeof(char)*2);
  char *month = (char*) malloc(sizeof(char)*2);
  char *year = (char*) malloc(sizeof(char)*4);

  while(counter <= strlen(date_time)){
    if(date_time[counter] == '/'){
      if(flag == false){
        end = counter;
        flag = true;
        day = returning(str, end, date_time);
        str = counter+1;
      }
      else{
        end = counter;
        month = returning(str, end, date_time);
        str = counter+1;
        end = strlen(date_time);
        year = returning(str, end, date_time);
      }
    }
    counter++;
  }

  // check

  if(atoi(day) < 1 || atoi(day) > 31){
    printf("false date");
    acceptable = false;
  }

  if(atoi(month) < 1 || atoi(month) > 12){
    printf("false date");
    acceptable = false;
  }

  if(atoi(month) == 4 && atoi(day) > 28){
    printf("false date");
    acceptable = false;
  }
  if(atoi(day) == 31 && (atoi(month) == 4 || (atoi(month) == 6) || (atoi(month) == 9) || (atoi(month) == 11))){
    printf("false date");
    acceptable = false;
  }

  return acceptable;
}

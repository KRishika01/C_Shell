#ifndef MYSHRC_H
#define MYSHRC_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Execution.h"

void insert(char *alias,char *input);
void *moving(void *dest,void *src,int len);
char *aliasPresence(char *input);
void aliasExecution(char *input);
void myshrc_reading(char *file);

#endif
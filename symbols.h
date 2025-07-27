#ifndef SYMBOLS_H
#define SYMBOLS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>


void symbolsRedirection(char *data);
void sysmbolExecution(char *input,char *output,int flag,char *data);
void removespaces_redirection(char *input);

#endif
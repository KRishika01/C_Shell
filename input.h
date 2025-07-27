#ifndef INPUT_H
#define INPUT_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<ctype.h>

void tokenisation_with_spaces(char **array,char *path,int *counter);
void tokenisation_with_ampresand(char **array,char *path,int *counter);
void tokenisation_with_semicolon(char **array,char *path,int *counter);

#endif
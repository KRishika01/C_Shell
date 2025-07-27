#ifndef REVEAL_H
#define REVEAL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<sys/stat.h>
#include<time.h>
#include<libgen.h>
#include "hop.h"


#define COLOR_R "\033[0m"
#define COLOR_EXEC_GREEN "\033[1;32m"
#define COLOR_DIR_GREEN "\033[1;34m"
#define FILE_COLOR "\033[0m" 

int compare(const void *a,const void *b);
void JustReveal(char *data);
void flag_a_Execution(char *data);
void permissionsRequired(mode_t mode);
void flag_l_Execution(char *data);
void colouring(char *path);
void flag_al_la_Execution(char *data);
void revealExecution(int counter,char *array[],char *data,char *prepath);
void revealFlags(char *input,int flag_a,int flag_l,char *path,char *prepath);

#endif
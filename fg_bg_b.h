#ifndef FG_BG_b_H
#define FG_bG_B_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<dirent.h>
#include<sys/stat.h>
#include<signal.h>
#include<errno.h>

#include "activities.h"

void bringing_to_fg(char **array,int *counter);
void bringing_to_bg(char **array,int *counter);
void *function_mem(int number,void *pointer,size_t nu);

#endif
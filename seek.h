#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/stat.h>

void seek(char *path,char *data,int dd,int ff,int ts);
void flags_execution_seek(char **array,int counter);
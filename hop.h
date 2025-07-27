#ifndef HOP_H
#define hOP_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>



extern char presentWorkingDirectory[4096];
extern char previousDirectory[4096];

void hopFlags(char *path);

#endif
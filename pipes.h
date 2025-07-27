#ifndef PIPES_H
#define PIPES_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

void pipes_execution(char *input);
void removingspaces_pipes(char *input);

#endif
#ifndef MAN_H
#define MAN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>

void manPage_execution(char *websiteName,char **array);
void subManPage(char **array,int req_socket);

#endif
#ifndef DISPLAY_H
#define DISPLAY_h

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/utsname.h>

#include "hop.h"
#include "bg_fg.h"

extern char *username;
extern struct utsname information;
extern char cwd_in_display[4096];

char *printRelativepath(char *homeDirectory,char *path);
void displayuserData();

#endif
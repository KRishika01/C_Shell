#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/utsname.h>

extern char *username;
extern struct utsname information;
extern char cwd_in_display[4096];

char *printRelativepath(char *homeDirectory,char *path);
void displayuserData(char *data);
void displayUpdatedData(int timetaken,char *input);
void updatedata(char **array,char *data,int timetaken);

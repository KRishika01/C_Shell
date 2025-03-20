#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<signal.h>
#include<sys/time.h>
#include <ctype.h>

extern int timetaken_in_sleep;
extern char timetaken_update[4096];

void BackgroundProcess(char**array,char * input);
void ForegroundProcess(char **array,char *input);
void bagr_fogr(char *input);
void status_background_process(char *input);
void foreground_background(int flag_bg,char *input);
void *function_m(int number,void *pointer,size_t nu);
#ifndef BG_FG_H
#define BG_FG_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<signal.h>
#include<sys/time.h>
#include <ctype.h>
#include <sys/types.h>
#include <errno.h>

#include "display.h"
#include "activities.h"
#include "ping.h"
#include "ping.h"

extern int timetaken_in_sleep;
extern char timetaken_update[4096];
extern int returnCode_in_bg_fg;


void bagr_fogr(char *input);
void status_background_process(char *input);
void foreground_background(int flag_bg,char *input);
void *function_m(int number,void *pointer,size_t nu);
void command_background(int pid,int size,char *command);

#endif
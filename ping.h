#ifndef PING_H
#define PING_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/signal.h>
#include "activities.h"
#include "display.h"
#include "bg_fg.h"


extern int pid_in_ping;
extern int ctrlC_flag;
extern int fg_running;

void ctrlC_execution();
void ctrlD_execution();
void pingExecution(char **array);

#endif
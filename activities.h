#ifndef ACTIVITIES_H
#define ACTIVITIES_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>

extern char *array_to_store_commands[4096];
extern int array_to_store_pids[4096];
extern char *status_to_strore[4096];
extern int counter_in_activities;
extern int bg_in_activities;
extern int bg_flag_activities[4096];
extern int signals_stop[4096];


void activityDetails();
int compare_activities(const void *a,const void * b);
void removingProcess(int returnCode);

#endif
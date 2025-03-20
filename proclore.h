#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

void get_pid();
void getstatus(int pid);
void getprocess_group(int pid);
void getvirtual_path(int pid);
void getExecutablePath(int pid);
void proclore(int pid);
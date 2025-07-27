#include "fg_bg_b.h"

void *function_mem(int number,void *pointer,size_t nu) {
    char *poi = (char *)pointer;
    char num = (char)number;

    while(nu--) {
        *poi++ = num;
    }
    return pointer;
}

void bringing_to_fg(char **array,int *counter) {
    int gpid = atoi(array[1]);
    int flag;

    if(gpid >= 0) {

        if(kill(gpid,0) == -1) {
            perror("No such process exists");
            return;
        } 
        tcsetpgrp(STDIN_FILENO,gpid);
        signal(SIGTTIN,SIG_IGN);
        signal(SIGTTOU,SIG_IGN);

        if(kill(gpid,SIGCONT) == 0) {
            printf("Bringing process [%d] to foreground.\n",gpid);
            (*counter)--;
            int data;
            flag = gpid;
            waitpid(gpid,&data,WUNTRACED);
            if(WIFSTOPPED(data)) {
                printf("Process [%d] stopped again\n",gpid);
            }
            flag = 0;
        }
       
        tcsetpgrp(STDIN_FILENO,getpgrp());

        signal(SIGTTIN,SIG_DFL);
        signal(SIGTTOU,SIG_DFL);

    }
    else {
        printf("No such process exists\n");
    }
}
void bringing_to_bg(char **array,int *counter) {
    if(array[1] != NULL) {
        int gpid = atoi(array[1]);

        if(gpid > 0) {
            int sts;
            if(waitpid(gpid,&sts,WNOHANG|WUNTRACED) > 0) {
                if(kill(gpid,SIGCONT) == 0) {
                    printf("Continuing process [%d] in background\n",gpid);
                }
                else {
                    perror("Error in bg");
                    return;
                }
            }
            else {
                perror("Invalid PID");
                return;
            }
        }
    }
}




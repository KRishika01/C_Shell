
#include "proclore.h"

void get_pid(int pid) {
    printf("pid: %d\n",pid);
}

void getstatus(int pid) {
    char path[1024];
    char *status_open;
    char *status_close;
    snprintf(path,sizeof(path),"/proc/%d/status",pid);

    FILE *fstatus = fopen(path,"r");
    if(fstatus == NULL) {
        perror("fstatus");
        // exit(1);
        return;
    }

    char array[4096];
    char sign = '\0';
    int b_pid = tcgetpgrp(STDIN_FILENO);
    
    if(pid == b_pid) {
        sign = '+';
    }
    else {
        sign = '\0';
    }

    do {
        if(fgets(array,sizeof(array),fstatus) != NULL) {
            if(strncmp(array,"State:",6) == 0) {
                status_open = strchr(array, ':') + 2;

                status_close = strchr(status_open,' ');
                if(status_close != NULL) {
                    *status_close = '\0';
                }
                if(sign == '+') {
                    printf("Process Status: %s+\n",status_open);
                }
                else {
                    printf("Process Status:%s\n",status_open);
                }
                break;
            }
        }
    } while(fgets(array,sizeof(array),fstatus) != NULL);

    fclose(fstatus);
}

void getprocess_group(int pid) {
    printf("Process group: %d\n",getpgid(pid));
}

void getvirtual_path(int pid) {
    char virtual_path[1024];
    snprintf(virtual_path,sizeof(virtual_path),"/proc/%d/statm",pid);

    FILE *fvir = fopen(virtual_path,"r");
    if(fvir == NULL) {
        perror("fvir");
        return;
        // exit(1);
    }
    int virtual_size;
    fscanf(fvir,"%d",&virtual_size);
    printf("Virtual Memory: %d\n",virtual_size);
    fclose(fvir);
} 

void getExecutablePath(int pid) {
    char exec_path[1024];
    snprintf(exec_path,sizeof(exec_path),"/proc/%d/cmdline",pid);

    FILE *fexec = fopen(exec_path,"r");
    if(fexec == NULL) {
        perror("fexec");
        return;
        // exit(1);
    }

    int dataRead;
    dataRead = fread(exec_path,1,sizeof(exec_path),fexec);

    if(dataRead > 0) {
        for(int k=0;k<dataRead;k++) {
            if(exec_path[k] == '\0') {
                exec_path[k] = ' ';
            }
        }
        exec_path[dataRead] = '\0';
    }
    printf("Executable path: %s\n",exec_path);
    fclose(fexec);
}

void proclore(int pid) {
    get_pid(pid);
    getstatus(pid);
    getprocess_group(pid);
    getvirtual_path(pid);
    getExecutablePath(pid);
}

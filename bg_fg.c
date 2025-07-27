#include "bg_fg.h"

int timetaken_in_sleep;
char timetaken_update[4096];
int returnCode_in_bg_fg;

void command_background(int pid,int size,char *command) {
    char path_in[4096];
    FILE *fcommand;

    snprintf(path_in,sizeof(path_in),"/proc/%d/comm",pid);
    fcommand = fopen(path_in,"r");
    if(fcommand != NULL) {
        if(fgets(command,sizeof(command),fcommand) != NULL) {
            command[strcspn(command,"\n")] = '\0';
        }
        else {
            snprintf(command,size,"Failed");
        }
        fclose(fcommand);
    }
    else {
        snprintf(command,size,"Unknown");
    }
}

void status_background_process(char *input) {
    int status;
    int returnCode_1 = waitpid(-1,&status,WNOHANG);
    while(returnCode_1 > 0) {
        if(WIFEXITED(status)) {
            printf("Process exited normally with status (%d) (PID : %d)\n",WEXITSTATUS(status),returnCode_1);
        }
        else if(WIFSIGNALED(status)){
            printf("Process terminated by signal (%d) (PID : %d)\n",WTERMSIG(status),returnCode_1);
        }
        else if(WIFSTOPPED(status)) {
            printf("Process stopped by the signal (%d) (PID : %d)\n",WSTOPSIG(status),returnCode_1);
        }
        returnCode_1 = waitpid(-1,&status,WNOHANG);
    }
}

void foreground_background(int flag_bg,char *input) {
    char dup_printingdata[4096];
    struct timeval initiation;
    struct timeval termination;

    char *array[4096];
    int counter = 0;
    char *word = strtok(input," \t");
    do {
        if(word != NULL && counter < 4095) {
            array[counter++] = word;
            word = strtok(NULL," \t");
        }
    } while(word != NULL && counter < 4095);
    array[counter] = NULL;


    gettimeofday(&initiation,NULL);

    returnCode_in_bg_fg = fork();
    if(returnCode_in_bg_fg < 0) {
        perror("Error in forking");
        return;
    }
    else if(returnCode_in_bg_fg > 0) {
        // pid_in_ping = returnCode;
        if(!flag_bg) {
            fg_running = 1;
            pid_in_ping = returnCode_in_bg_fg;
            char data[4095];
            int sts;
            waitpid(returnCode_in_bg_fg,NULL,0);
            gettimeofday(&termination,NULL);
            timetaken_in_sleep = termination.tv_sec - initiation.tv_sec;

            if(timetaken_in_sleep > 2 && strcmp(array[0],"sleep") == 0) {
                printf("\n%s : %d\n",input,timetaken_in_sleep);
                
            }
        }
        else {
            
            fg_running = 0;
            printf("[%d]\n",returnCode_in_bg_fg);
        }
    }
    else {
        if(flag_bg) {
            setpgid(0,0);       // After bg command if we enter CTRL-C then to not do anything we use this
        }
        execvp(array[0],array);
        if(strcmp(input,"exit") != 0) {
            printf("%s is not a valid command\n",input);
        }
        return;
    }
}


char *removing(char *string) {
    if(string == NULL) {
        return string;
    }
    while(isspace(*string)) {
        string++;
    }
    char *last = string + strlen(string) - 1;
    while(last > string && isspace(*last)) {
        last--;
    }
    *(last+1) = 0;
    return string;
}

void *function_m(int number,void *pointer,size_t nu) {
    char *poi = (char *)pointer;
    char num = (char)number;

    while(nu--) {
        *poi++ = num;
    }
    return pointer;
}

void bagr_fogr(char *input) {
    char *array[4096];
    int duparray[4096];
    int counter = 0;
    int aanndd_counter = 0;

    function_m(0,duparray,sizeof(duparray));
    char *word = strtok(input,";");
    do {
        if(word != NULL) {
            // counter++;
            array[counter++] = word;
            word = strtok(NULL,";");
        }
    } while(word != NULL);

    for(int i=0;i<counter;i++) {
        char *data = removing(array[i]);
        if(strlen(data) == 0) {
            continue;
        }
        char *aanndd = strchr(data,'&');
        do {
            if(aanndd != NULL) {
                int flag_counter = aanndd - data;
                if(flag_counter > 0) {
                    char *input_dup = strndup(data,flag_counter);
                    input_dup = removing(input_dup);

                    if(strlen(input_dup) <= 0) {
                        free(input_dup);
                    }
                    else {
                        array[aanndd_counter] = input_dup;
                        duparray[aanndd_counter] = 1;
                        aanndd_counter++;
                    }
                }
                data = aanndd + 1;
                data = removing(data);
                aanndd = strchr(data,'&');
            }
        } while(aanndd != NULL);
        data = removing(data);
        if(*data != '\0') {
            array[aanndd_counter] = data;
            duparray[aanndd_counter] = 0;
            aanndd_counter++;
        }
    }
    for(int i=0;i<aanndd_counter;i++) {
        // printf("%d\n",aanndd_counter);
        char *psr = array[i];
        int bg = duparray[i];
        if(strlen(psr) > 0) {
           foreground_background(bg,psr);
        }
    }
}

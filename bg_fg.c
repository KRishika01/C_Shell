#include "bg_fg.h"
#include "display.h"

int timetaken_in_sleep;
char timetaken_update[4096];

void status_background_process(char *input) {
    int status;
    // int returnCode_1 = waitpid(-1,&status,WNOHANG);
    int returnCode_1;

    while(returnCode_1 = waitpid(-1,&status,WNOHANG) > 0) {
        if(WIFEXITED(status)) {
            // printf("%s exited %d\n",data,WEXITSTATUS(status));
            printf("Sleep exited normally (%d)\n",getpid());
        }
        else if(WIFSIGNALED(status)) {
            // printf("%s exited abnormally %d\n",data,WIFSIGNALED(status));
            printf("Sleep exited abnormally (%d)\n",getpid());
        }
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

    int returnCode = fork();
    if(returnCode < 0) {
        perror("Error in forking");
        return;
    }
    else if(returnCode > 0) {
        if(!flag_bg) {
            char data[4095];
            int sts;
            waitpid(returnCode,NULL,0);
            gettimeofday(&termination,NULL);
            timetaken_in_sleep = termination.tv_sec - initiation.tv_sec;

            if(timetaken_in_sleep > 2 && strcmp(array[0],"sleep") == 0) {
                printf("\n%s : %d\n",input,timetaken_in_sleep);
                
            }
        }
        else {
            printf("[%d]\n",getpid());
        }
    }
    else {
        execvp(array[0],array);
        // perror("Error in execvp");
        if(strcmp(input,"exit") != 0) {
            printf("%s is not a valid command\n",input);
        }
        return;
    }
}

// void updatingprompt(char *input,int *flag_update,char *upd_data) {
//     struct timeval initiation;
//     struct timeval termination;

//     gettimeofday(&initiation,NULL);
//     foreground_background(0,input);

//     gettimeofday(&termination,NULL);
//     int timetaken = termination.tv_sec - initiation.tv_sec;
//     if(timetaken > 2) {
//         *flag_update = 1;
//     }
// }

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

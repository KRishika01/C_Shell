#include "Execution.h"
#include "reveal.h"

void commands_execution(char *input) {
    char *array[4096];
    char prepath[4096];
    int counter = 0;
    char dupinput[1024];
    char *path_in_execution;
    strcpy(dupinput,input);

    char *word = strtok(input," ");
    while(word != NULL) {
        array[counter++] = word;
        word = strtok(NULL," ");
    }
    array[counter] = NULL;

    if(counter > 0) {
        if(strcmp(array[0],"log") == 0) {
            if(array[1] != NULL && strcmp(array[1],"purge") == 0) {
                deletingTheCommands();
            }
            else if(array[1] != NULL && strncmp(array[1],"execute",11) == 0) {
                int value = atoi(input+12);
                execute_commands_log(value);
            }
            else {
                printing_file_data();
            }
        }
        else if(strcmp(array[0],"hop") == 0) {
            if(counter == 1) {
                hopFlags("~");
            }
            else {
                for(int i=1;i<counter;i++) {
                    hopFlags(array[i]);
                }
            }
        }
        else if(strcmp(array[0],"reveal") == 0) {
            if(counter > 0 && array[counter-1][0] == '/') {
                path_in_execution = array[counter-1];
            }
            else {
                path_in_execution = ".";
            }
            revealExecution(counter,array,path_in_execution,prepath);
        }
        else if(strncmp(array[0],"proclore",8) == 0) {
            int pid = 0;
            char *string = input+9;

            if(*string != '\0') {
                pid = atoi(string);
            }
            else {
                pid = getpid();
            }
            if(pid > 0) {
                proclore(pid);
            }
            else {
                perror("proclore");
            }
        }
        else if(strcmp(array[0],"seek") == 0) {
            flags_execution_seek(array,counter);
        }
        // else if(strcmp(array[0],"hop") != 0 && strcmp(array[0],"reveal") != 0 && strcmp(array[0],"log") != 0 && strcmp(array[0],"proclore") != 0 && strcmp(array[0],"seek") != 0){
        //     bagr_fogr(dupinput);
        // }
        else {
            bagr_fogr(dupinput);
        }
    }
}
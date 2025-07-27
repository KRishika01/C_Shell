#include "pipes.h"
#include "bg_fg.h"
#include "Execution.h"

void removingspaces_pipes(char *input) {
    char data[4096];
    int flag = 0;

    for(int i=0;i<strlen(input);i++) {
        if(input[i] == '|') {
            while(flag > 0 && (data[flag-1] == ' ' || data[flag-1] == '\t') ) {
                flag--;
            }
            data[flag++] = input[i];

            while(input[i+1] == ' ' || input[i+1] == '\t') {
                i++;
            }
        }
        else {
            data[flag++] = input[i];
        }
    }
    data[flag] = '\0';
    strcpy(input,data);
}

void pipes_execution(char *input) {
    char *array[4096];
    int pipes_array[2];
    int counter = 0;
    int previousCounter = -1;

    removingspaces_pipes(input);

    char *word = strtok(input,"|");
    while(word != NULL) {
        array[counter++] = strdup(word);
        word = strtok(NULL,"|");
    }

    for(int i=0;i<counter;i++) {
        if(counter - 1 > i) {
            if(pipe(pipes_array) < 0) {
                perror("Error in piping in pipes_execution");
                return;
            }
        }

        int returnCode = fork();
        if(returnCode < 0) {
            perror("Error in forking in pipes_execution");
            return;
        }
        else if(returnCode > 0) {
            wait(NULL);

            if(counter-1 > i) {
                close(pipes_array[1]);
            }
            previousCounter = pipes_array[0];
        }
        else {
            if(previousCounter != -1) {
                dup2(previousCounter,STDIN_FILENO);
                close(previousCounter);
            }
            if(counter-1 > i) {
                close(pipes_array[0]);
                dup2(pipes_array[1],STDOUT_FILENO);
                close(pipes_array[1]);
            }
            commands_execution(array[i]);
            exit(0);
        }
    }
}
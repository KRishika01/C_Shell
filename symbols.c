#include "symbols.h"
#include "bg_fg.h"
#include "Execution.h"

void removespaces_redirection(char *input) {
    char data[4096];
    int flag = 0;

    for(int i=0;i<strlen(input);i++) {
        if(input[i] == '<' || input[i] == '>' || (input[i] == '>' && input[i+1] == '>')) {
            while(flag > 0 && data[flag-1] == ' ') {
                flag--;
            }

            data[flag++] = input[i];

            if(input[i] == '>' && input[i+1] == '>') {
                data[flag++] = input[++i];
            }
            if(input[i] == '>' && input[i+1] == ' ' && input[i+2] == '>') {
                printf("It is not a valid symbol\n");
            }

            while(input[i+1] == ' ') {
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

void sysmbolExecution(char *input,char *output,int flag,char *data) {
    // printf("coming\n");
    int returnCode = fork();
    // printf("%d\n",returnCode);
    if(returnCode < 0) {
        perror("Error in forking in symbolExecution");
        return;
    }
    else if(returnCode > 0) {
        // printf("%d\n",returnCode);
        // printf("waur\n");
        wait(NULL);
    }
    else {
        // printf("%d\n",returnCode);
        if(output != NULL) {
            int ofileDes;
            if(!flag) {
                ofileDes = open(output,O_CREAT|O_WRONLY|O_TRUNC,0644);
                if(ofileDes < 0) {
                    perror("Error in opening the output in >");
                    return;
                }
                dup2(ofileDes,STDOUT_FILENO);
                close(ofileDes);
            }
            else {
                ofileDes = open(output,O_CREAT|O_APPEND|O_WRONLY,0644);
                if(ofileDes < 0) {
                    perror("Error in opening the output in >>");
                    return;
                }
                dup2(ofileDes,STDOUT_FILENO);
                close(ofileDes);
            }
        }

        if(input != NULL) {
            int ifileDes;
            ifileDes = open(input,O_RDONLY);
            if(ifileDes < 0) {
                perror("Error in opening the input in <");
                return;
            }
            dup2(ifileDes,STDIN_FILENO);
            close(ifileDes);
        }
        // printf("%s\n",data);
        commands_execution(data);
        exit(0);
    }
}

void symbolsRedirection(char *data) {
    // printf("Came\n");
    int flag = 0;
    char *input = NULL;
    char * output = NULL;

    removespaces_redirection(data);

    char *ifileD = strstr(data,"<");
    char *ofileD = strstr(data,">");
    char *o_afileD = strstr(data,">>");

    if(o_afileD) {
        *ofileD = '\0';
        output = strtok(ofileD+2," ");
        flag = 1;
    }
    else if(ofileD) {
        *ofileD = '\0';
        output = strtok(ofileD+1," ");
        flag = 0;
    }

    if(ifileD) {
        *ifileD = '\0';
        input = strtok(ifileD+1," ");
    }
    sysmbolExecution(input,output,flag,data);
}


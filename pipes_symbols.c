#include "pipes_symbols.h" 
#include "symbols.h"
#include "bg_fg.h"
#include "Execution.h"

void pipes_symbols_execution(char *input_given) {
    char *array[4096];
    int counter = 0;

    char *word_pipes = strtok(input_given,"|");
    while(word_pipes != NULL) {
        array[counter++] = strdup(word_pipes);
        word_pipes = strtok(NULL,"|");
    }

    int pipes_array[2];
    int input_fileD = 0;
    int output_fileD = 1;
    

    for(int i=0;i<counter;i++) {
        char data[4096];
        int input_flag = 0;
        int output_flag = 0;
        char *input = NULL;
        char *output = NULL;

        snprintf(data,sizeof(data),"%s",array[i]);

        char *word_t = strtok(data," \t");
        while(word_t != NULL) {
            if(strcmp(word_t,"<") == 0) {
                input_flag = 1;
                word_t = strtok(NULL," \t");
                if(word_t == NULL) {
                    perror("Error in tokenising the word_t in < pipes_symbols_execution");
                    return;
                }
                input = word_t;
            }
            else if(strcmp(word_t,">") == 0) {
                output_flag = 1;
                word_t = strtok(NULL," \t");
                while(word_t == NULL) {
                    perror("Error in tokenising the word_t in > pipes_symbols_execution");
                    return;
                } 
                output = word_t;
            }
            word_t = strtok(NULL," \t");
        }

        if(output_flag) {
            output_fileD = open(output,O_WRONLY|O_CREAT|O_TRUNC,0644);
            if(output_fileD < 0) {
                perror("Error in opening the output file in pipes_symbols_execution");
                return;
            }
        }

        if(input_flag) {
            input_fileD = open(input,O_RDONLY);
            if(input_flag < 0) {
                perror("Error in opening the output file in pipes_symbols_execution");
                return;
            }
        }

        if(counter-1 > i) {
            if(pipe(pipes_array) < 0) {
                perror("Error in piping");
                return;
            }
        }

        int returnCode = fork();
        if(returnCode < 0) {
            perror("Error in forking");
            return;
        }
        else if(returnCode > 0) {
            if(counter-1 > i) {
                close(pipes_array[1]);
                if(input_fileD != 0) {
                    close(input_fileD);
                }
                input_fileD = pipes_array[0];
            }
            wait(NULL);
        }
        else {
            if(counter-1 > i) {
                close(pipes_array[0]);
                if(input_fileD != 0) {
                    dup2(input_fileD,STDIN_FILENO);
                    close(input_fileD);
                }
                dup2(pipes_array[1],STDOUT_FILENO);
                close(pipes_array[1]);
            }
            else {
                if(output_flag) {
                    dup2(output_fileD,STDOUT_FILENO);
                    close(output_fileD);
                }
                if(input_fileD != 0) {
                    dup2(input_fileD,STDIN_FILENO);
                    close(input_fileD);
                }
            }
            commands_execution(array[i]);
            exit(0);
        }
    }
}
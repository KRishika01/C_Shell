#include "input.h"

void tokenisation_with_semicolon(char **array,char *path,int *counter) {
    *counter = 0;
    char *word = strtok(path,";");

    while(word != NULL) {
        char *tk = word + strlen(word) - 1;
        while(tk > word && isspace(*tk)) {
            tk--;
        }
        *(tk+1) = '\0';

        array[(*counter)++] = word;
        word = strtok(NULL,";");
    }
    array[*counter] = NULL;
}

void tokenisation_with_ampresand(char **array,char *path,int *counter) {
    *counter = 0;
    char *word = strtok(path,"&");

    while(word != NULL) {
        char *tk = word + strlen(word) - 1;
        while(tk > word && isspace(*tk)) {
            tk--;
        }
        *(tk+1) = '\0';

        array[(*counter)++] = word;
        word = strtok(NULL,"&");
    }
    array[*counter] = NULL;
}


void tokenisation_with_spaces(char **array,char *path,int *counter) {
    *counter = 0;
    char *word = strtok(path," \t");
    do {
        if(word != NULL) {
            array[(*counter)++] = word;
            word = strtok(NULL," \t");
        }
    } while(word != NULL);
    array[(*counter)] = NULL;
}

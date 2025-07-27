#include "myshrc.h"

char array_for_alias[100][100];
char commands_in_alias[100][100];
int counter_in_myshrc = 0;

void insert(char *alias,char *input) {
    for(int i=0;i<counter_in_myshrc;i++) {
        // strncpy(array_for_alias[counter_in_myshrc],alias,99);
        // strncpy(commands_in_alias[counter_in_myshrc],input,99);
        if(strcmp(alias,array_for_alias[i]) == 0) {
            strncpy(commands_in_alias[counter_in_myshrc],input,99);
            commands_in_alias[i][99] = '\0';   
            return;
        }
        // counter_in_myshrc++;
    }
    if (counter_in_myshrc < 100) {
        strncpy(array_for_alias[counter_in_myshrc], alias, 100 - 1);
        strncpy(commands_in_alias[counter_in_myshrc], input, 100 - 1);
        array_for_alias[counter_in_myshrc][100 - 1] = '\0'; 
        commands_in_alias[counter_in_myshrc][100 - 1] = '\0'; 
        counter_in_myshrc++;
    }

}

void *moving(void *dest,void *src,int len) {
    unsigned char *d = (unsigned char *)dest;
    unsigned char *s = (unsigned char *)src;

    if(d == s) {
        return dest;
    }
    else if(d > s) {
        for(int i=len;i>0;i--) {
            d[i-1] = s[i-1];
        }
    }
    else {
        for(int i=0;i<len;i++) {
            d[i] = s[i];
        }
    }
    return dest;
}

char *aliasPresence(char *input) {
    for(int i=0;i<counter_in_myshrc;i++) {
        if(strcmp(input,array_for_alias[i]) == 0) {
            char *word = strdup(commands_in_alias[i]);
            if (strlen(word) > 1 && word[0] == '"' && word[strlen(word) - 1] == '"') {
                word[strlen(word) - 1] = '\0';
                moving(word, word + 1, strlen(word) - 2);
                word[strlen(word) - 2] = '\0';
            }
            return word;
        }
    }
    return strdup(input);
}

void myshrc_reading(char *file) {
    FILE *fshrc = fopen(file,"r");
    if(fshrc == NULL) {
        // perror("Error in opening the file fshrc");
        return;
    }
    char word[4096];
    while (fgets(word, sizeof(word), fshrc)) {
        word[strcspn(word, "\n")] = '\0';

        if (strncmp(word, "alias ", 6) == 0) {
            char *dupword = word + 6;
            char *ali = strtok(dupword, "=");
            char *alico = strtok(NULL, "");

            if (ali && alico) {
                if (strlen(alico) > 0 && alico[0] == '"' && alico[strlen(alico) - 1] == '"') {
                    alico[strlen(alico) - 1] = '\0';
                    moving(alico, alico + 1, strlen(alico) - 2);
                }
                insert(ali, alico);

                // printf("Alias added: %s -> %s\n", ali, alico);
            }
        }
    }
    fclose(fshrc);
}

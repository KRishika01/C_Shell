#include "display.h"
#include "input.h"
#include "hop.h"
#include "proclore.h"
#include "log.h"
#include "reveal.h"
#include "seek.h"
#include "Execution.h"
#include "bg_fg.h"

int main() {
    getcwd(presentWorkingDirectory,sizeof(presentWorkingDirectory));
    getcwd(previousDirectory,sizeof(previousDirectory));

    char input[4096];
    char data[4096];
    char dupprompt[4096];
    char data_in_display[4096];
    char *path;
    int pid = 0;
    openingFile();
    readDataFromFile();
    while(1) {
        char *array[4096];
        int counter = 0;
        displayuserData(data);
        fgets(input,sizeof(input),stdin);
        
        input[strcspn(input,"\n")] = 0;
        addingTofile(input);
        status_background_process(input);
        char *word = strtok(input,";\t");
        while(word != NULL) {
            array[counter++] = word;
            word = strtok(NULL,";\t");
        }
        array[counter] = NULL;

        for(int i=0;i<counter;i++) {
            commands_execution(array[i]);
        }
        if(strcmp(input,"exit") == 0) {
            break;
        }
    }
}
#include "Execution.h"

void commands_execution(char *input) {
    int counter_fg = 0;
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
        if(strcmp(array[0],"log") == 0 && !strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,">>") && !strstr(dupinput,"<")) {
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
        else if(strcmp(array[0],"hop") == 0 && !strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,">>") && !strstr(dupinput,"<")) {
            if(counter == 1) {
                hopFlags("~");
            }
            else {
                for(int i=1;i<counter;i++) {
                    hopFlags(array[i]);
                }
            }
        }
        else if(strcmp(array[0],"reveal")== 0 && !strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,">>") && !strstr(dupinput,"<")) {
            if(counter > 0 && array[counter-1][0] == '/') {
                path_in_execution = array[counter-1];
            }
            else {
                path_in_execution = ".";
            }
            revealExecution(counter,array,path_in_execution,prepath);
        }
        else if(strcmp(array[0],"proclore") == 0 && !strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,">>") && !strstr(dupinput,"<")) {
            int pid;
            pid = getpid();
            if(counter == 1) {
                proclore(pid);
            }
            else {
                pid = atoi(array[1]);
                proclore(pid);
            }
        }
        else if(strcmp(array[0],"seek") == 0 && !strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,">>") && !strstr(dupinput,"<")) {
            flags_execution_seek(array,counter);
        }
        else if(strcmp(input,"activities") == 0 && !strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,">>") && !strstr(dupinput,"<")) {
            activityDetails();   
        }
        else if(!strstr(dupinput,"|") && (strstr(dupinput,">") || strstr(dupinput,">>") || strstr(dupinput,"<"))) {
            symbolsRedirection(dupinput);
        }
        else if(strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,"<") && !strstr(dupinput,">>")) {
            pipes_execution(dupinput);
        }
        else if(strstr(dupinput,"|") && (strstr(dupinput,">") || strstr(dupinput,">>") || strstr(dupinput,"<"))) {
            pipes_symbols_execution(dupinput);
        }
        else if(strstr(input,"fg") && !strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,">>") && !strstr(dupinput,"<")) {
            bringing_to_fg(array,&counter_fg);
        }
        else if(strstr(input,"bg") && !strstr(dupinput,"|") && !strstr(dupinput,">") && !strstr(dupinput,">>") && !strstr(dupinput,"<")) {
            bringing_to_bg(array,&counter_fg);
        }
        else if(strstr(dupinput,"ping")) {
            pingExecution(array);
        }
        else if(strcmp(array[0],"iMan") == 0) {
            char *website = "man.he.net";
            manPage_execution(website,array);   
        }

        else {
            bagr_fogr(dupinput);
        }   
    }
}
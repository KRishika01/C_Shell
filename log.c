/* USING FILE POINTER */
/* Using circular buffer for having only 15 commands stored in file */

#include "log.h"
#include "Execution.h"

char array[MAX_SIZE][4096];
int counter = 0;
int temp = 0;

void openingFile() {
    int fileD = open(FILE_PATH,O_CREAT,0644);
    if(fileD == -1) {
        perror("Error in opening the file in opening");
    }
    close(fileD);
} 

void readDataFromFile() {
    FILE *fileread = fopen(FILE_PATH,"r");
    if(fileread == NULL) {
        printf("Error in opening the file in reading");
        return;
    }
    char data[4096];
    do {
        if(fgets(data,sizeof(data),fileread) == NULL) {
            break;
        }
        data[strcspn(data,"\n")] = '\0';
        strncpy(array[counter],data,4095);
        // array[counter][1023] = '\0';
        counter++;
        if(counter >= MAX_SIZE) {
            temp = (temp+1) % MAX_SIZE;
            counter = MAX_SIZE;
        }  
    } while(1);
   fclose(fileread);
}
 
void writeToFile() {
    FILE *filewrite = fopen(FILE_PATH,"w");
    if(filewrite == NULL) {
        printf("Error in opening the file in writingtofile");
        return;
    }
    for(int i=0;i<counter;i++) {
        int id = (temp+i) % MAX_SIZE;
        fprintf(filewrite,"%s\n",array[id]);
    }
    // int id = (counter+temp-1) % MAX_SIZE;
    // fprintf(filewrite,"%s\n",array[id]);
    fclose(filewrite);
}   

void addingTofile(char *input) {
    // if commands are same don't add them 
    if(counter > 0) {
        int id = (counter+temp-1) % MAX_SIZE;
        if(strcmp(array[id],input) == 0) {
            return;
        }
    }

    if(strstr(input,"log") != NULL) {   // For not wrirting commamds related to log
        return;
    }
    int id = (counter+temp) % MAX_SIZE;
    strncpy(array[id],input,4095);
    array[id][1023] = '\0';
    if(counter >= MAX_SIZE) {
        temp = (temp+1) % MAX_SIZE;
    }
    else {
        counter++;
    }
    writeToFile();
}

void deletingTheCommands() {
    counter= 0;
    temp = 0;
    FILE *filedelete = fopen(FILE_PATH,"w");
    if(filedelete != NULL) {
        fclose(filedelete);
    }
}

void printing_file_data() {
    for(int i=0;i<counter;i++) {
        int id = (temp+i) % MAX_SIZE;    
        printf("%s\n",array[id]);
    }
}

void execute_commands_log(int value) {
    if(value < 1 || value > counter) {
        printf("Invalid value in log execute");
        return;
    }
    int id = (temp+counter-value) % MAX_SIZE;
    // printf("Executing Command : %s\n",array[id]);
    // printf("%s\n",array[id]);
    if(strcmp(array[counter-1],array[id]) != 0) {
        addingTofile(array[id]);
    }
    commands_execution(array[id]);
    
}

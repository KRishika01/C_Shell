#include "seek.h"
char duparray[4096];
int fileCounter = 0;
int directoryCounter = 0;

void seek(char *path,char *data,int dd,int ff,int ts) {
    char *path_seek = ".";
    
    // getcwd(path,sizeof(path));
    if(strcmp(path,path_seek) == 0) {
        getcwd(path,sizeof(path));
    }

    struct dirent *directory;
    DIR *dir;
    dir = opendir(path);

    do {
        directory = readdir(dir);

        if(directory == NULL) {
            return;
        }

        if(directory->d_name[0] == '.') {
            continue;
        }
        char path_file[4096];
        struct stat file;
        strcpy(path_file,path);
        strcat(path_file,"/");
        strcat(path_file,directory->d_name);
        char *word = strtok(directory->d_name,".");

        if((strcmp(word,data) == 0) || (strcmp(directory->d_name,data) == 0)) {
            if(stat(path_file,&file) == 0 && S_ISDIR(file.st_mode)) {
                if(dd || !ff) {
                    directoryCounter++;
                    strcpy(duparray,path_file);
                    printf("\e[36m%s\e[m\n",path_file);
                }
            }
            else {
                if(ff || !dd) {
                    fileCounter++;
                    strcpy(duparray,path_file);
                    printf("\e[32m%s\e[m\n",path_file);
                }
            }
        }
        if(stat(path_file,&file) == 0 && S_ISDIR(file.st_mode)) {
            seek(path_file,data,dd,ff,ts);
        } 
    } while(directory != NULL);
    closedir(dir);
}

void flags_execution_seek(char **array,int counter) {
    fileCounter = 0;
    directoryCounter = 0;
    int flag_ff = 0;
    int flag_dd = 0;
    int flag_ts = 0;

    if(counter <= 1) {
        printf("Error in giving the file\n");
        return;
    }

    if((counter > 1 && strcmp(array[1],"-f") == 0)) {
        flag_ff = 1;
    }
    if((counter > 1 && strcmp(array[1],"-e") == 0)) {
        flag_ts = 1;
    }
    if((counter > 1 && strcmp(array[1],"-d") == 0)) {
        flag_dd = 1;
    }
    if((counter > 2 && strcmp(array[2],"-f") == 0)) {
        flag_ff = 1;
    }
    if(counter > 2 && strcmp(array[2],"-e") == 0) {
        flag_ts = 1;
    }
    if((counter > 2 && strcmp(array[2],"-d") == 0)) {
        flag_dd = 1;
    }

    if(flag_dd + flag_ff + flag_ts == 0) {
        char *path_seek = ".";
        if(counter == 2) {
            array[2] = (char*)malloc(1024 * sizeof(char));
            strcpy(array[2],path_seek);
        }
        seek(array[2],array[1],flag_dd,flag_ff,flag_ts);
    }
    else if(flag_dd + flag_ff + flag_ts == 1) {
        char *path_seek = ".";
        if(counter == 3) {
            array[3] = (char*)malloc(1024 * sizeof(char));
            strcpy(array[3],path_seek);
        }
        seek(array[3],array[2],flag_dd,flag_ff,flag_ts);
    }
    else if(flag_dd + flag_ff + flag_ts == 2) {
        char *path_seek = ".";
        if(counter == 4) {
            array[4] = (char*)malloc(1024*sizeof(char));
            strcpy(array[4],path_seek);
        }   
        seek(array[4],array[3],flag_dd,flag_ff,flag_ts);

        if(flag_dd && flag_ff) {
            printf("Invalid Commands\n");
            return;
        }
    }
    if((fileCounter == 0) && (directoryCounter == 1) && flag_ts) {
        if(chdir(duparray)) {
            printf("Missing Permission for the task\n");
        }
    }
    if((fileCounter == 1) && (directoryCounter == 0) && flag_ts) {
        FILE *fileread = fopen(duparray,"r");
        if(fileread == NULL) {
            perror("Error in opening the file");
            return;
        }
        char data[4096];
        do {
            if(fgets(data,sizeof(data),fileread) != NULL) {
                printf("%s",data);
            }
        } while(fgets(data,sizeof(data),fileread) != NULL);
        printf("\n");
        fclose(fileread);
    }
    if(fileCounter == 0 && directoryCounter == 0) {
        printf("No Match Found\n");
    }
}
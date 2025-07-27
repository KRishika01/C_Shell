/*
In this it displays all the activities along with their name,PID and the state of the process
*/

#include "activities.h"

// This is to sort the activities that are present in the lexographical order.
int compare_activities(const void *a,const void * b) {
    return strcmp(*(const char**)a,*(const char**)b);
}

void activityDetails() {
    int pid = getpid();
    char spid[4096];

    sprintf(spid,"%d",pid);

    struct dirent *directory;
    DIR *dir;

    dir = opendir("/proc");
    if(dir == NULL) {
        perror("Error in opening the directory in actvityDetails");
        return;
    }

    do {
        directory = readdir(dir);

        if(directory != NULL) {
            if(directory->d_name[0] >= '0' && directory->d_name[0] <= '9') {
                char path_in_activities[4096];
                snprintf(path_in_activities,sizeof(path_in_activities),"/proc/%s/status",directory->d_name);

                FILE *fstatus = fopen(path_in_activities,"r");
                // if(fstatus == NULL) {
                //     perror("Error in opening file fstatus");
                //     return;
                // }

                if(fstatus != NULL) {
                    char data[4096];
                    char command[4096] = " ";
                    char status[4096] = " ";
                    int flag = 0;

                    while(fgets(data,sizeof(data),fstatus) != NULL) {
                        if(strncmp(data, "Name:",5) == 0) {
                            char *word = strstr(data,"Name:\t");

                            if(word != NULL) {
                                word += strlen("Name:\t");

                                int k = 0;
                                while(word[k] != '\0' && word[k] != '\n' && word[k] != ' ' && word[k] != '\t') {
                                    command[k] = word[k];
                                    k++;
                                }
                                command[k] = '\0';
                            }
                        }
                        else if(strncmp(data,"State:",6) == 0) {
                            char *word = strstr(data,"State:\t");

                            if(word != NULL) {
                                word += strlen("State:\t");

                                int k = 0;
                                while(word[k] != '\0' && word[k] != '\n' && word[k] != ' ' && word[k] != '\t') {
                                    status[k] = word[k];
                                    k++;
                                }
                                status[k] = '\0';
                            }
                        }
                        else if(strncmp(data,"PPid:",5) == 0) {
                            char *word = strtok(data+6,"\n");
                            if(strcmp(spid,word) == 0) {
                                flag = 1;
                            }
                        }
                    }
                    fclose(fstatus);

                    char dataPrint[4096];
                    if(strcmp(status,"R") == 0) {
                        strcpy(dataPrint,"Running");
                    }
                    else if(strcmp(status,"S") == 0) {
                        strcpy(dataPrint,"Running");
                    }
                    else if(strcmp(dataPrint,"Z") == 0) {
                        strcpy(dataPrint,"Stopped");
                    }
                    else {
                        strcpy(dataPrint,"Stopped");
                    }

                    if(flag) {
                        printf("[%s] : %s - %s\n",directory->d_name,command,dataPrint);
                    }
                }
            }
        }
    } while(directory != NULL);
    closedir(dir);
}

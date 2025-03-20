#include "display.h"
#include "hop.h"
#include "bg_fg.h"

char *username;
struct utsname information;
char cwd_in_display[4096];
char printingData[4096];

char *printRelativepath(char *homeDirectory,char *path) {
    static char relative[4096];
    if(strncmp(path,homeDirectory,strlen(homeDirectory)) == 0 && path[strlen(homeDirectory)] == '/') {
        strcpy(relative,path+strlen(homeDirectory)+1);
    }
    else {
        strcpy(relative,"~");
    }
    return relative;
}

void displayuserData(char *data) {
    char Ddata[1024];
    username = getlogin();
    if(username == NULL) {
        perror("Error in getting username");
        exit(1);
    }
    if(uname(&information) != 0) {
        perror("Error in getting the information");
        exit(1);
    }
    if(getcwd(cwd_in_display,sizeof(cwd_in_display)) == 0) {
        perror("Error in getting the current working directory");
        exit(1);
    }
    char *printingPath = printRelativepath(presentWorkingDirectory,cwd_in_display);
    printf("\033[1;32m<%s@%s\033[0m:\033[1;34m%s>\033[0m ",username,information.nodename,printingPath);
    // snprintf(data,size,"<%s@%s:%s> ",username,information.nodename,printingPath);
}

// void updatedata(char **array,char *data,int timetaken) {
//     printf("gone\n");
//     printf("%s\n",data);
//     printf("%s\n",array[0]);
//     strcat(data,array[0]);
//     strcat(data," : ");
//     char times[100];
//     sprintf(times,"%d",timetaken);
//     strcat(data,times);
//     strcat(data,">");
// }
#include "hop.h"
#include "display.h"
#include "input.h"

char presentWorkingDirectory[4096];
char previousDirectory[4096];

void hopFlags(char *path) {
    char pathToStore[4096];
    char cwd_in_hop[4096];
    char *relative;

    getcwd(cwd_in_hop,sizeof(cwd_in_hop));

    relative = printRelativepath(presentWorkingDirectory,cwd_in_hop);

    if(strcmp(path,"~") == 0) {
        strcpy(pathToStore,presentWorkingDirectory);
    }
    else if(strcmp(path,"-") == 0) {
        strcpy(pathToStore,previousDirectory);
    }
    else {
        strcpy(pathToStore,path);
    }

    if(chdir(pathToStore) == 0) {
        getcwd(pathToStore,sizeof(pathToStore));
        printf("%s\n",pathToStore);
        strcpy(previousDirectory,cwd_in_hop);
    }
    else {
        perror("Error in hop");
    }
}

#include "reveal.h"

int flag = 0;

int compare(const void *a,const void *b) {
    return strcmp(*(const char**)a,*(const char **)b);
}

void colouring(char *path) {
    struct stat file;
    if(stat(path,&file) == 0) {
        if(S_ISDIR(file.st_mode)) {
        printf(COLOR_DIR_GREEN "%s " COLOR_R,path);
        // printf("\n");
        }
        else if(S_IXUSR & file.st_mode) {
            printf(COLOR_EXEC_GREEN "%s " COLOR_R,path);
            // printf("\n");
        }
        else {
            printf(FILE_COLOR "%s " COLOR_R,path);
            // printf("\n");
        }
    }
    else {
        printf("%s ",path);
    }
}

void JustReveal(char *data) {
    struct dirent *directory;
    DIR *dir;
    char duppath[1024];

    if(strcmp(data,".") == 0 || data == NULL) {
        getcwd(duppath,sizeof(duppath));
    }
    else {
        strncpy(duppath,data,sizeof(duppath)-1);
        duppath[sizeof(duppath)-1] = '\0';
    }
    dir = opendir(duppath);
    int counter = 0;
    char *array[4096];
    char path_file[4096];

    if(dir == NULL) {
        perror("Error in opening the directory in reveal.c in JustReveal");
        return;
        // exit(1);
    }

    do {
        struct stat file;
        directory = readdir(dir);
        if(directory == NULL) {
            break;
        }

        if(directory->d_name[0] == '.') {
            continue;
        }

        if(counter >= 4096) {
            printf("Too many files");
            break;
        }

        array[counter] = strdup(directory->d_name);
        if(array[counter] == NULL) {
            perror("Error in duplicating");
            // exit(1);
            return;
        }
        counter++;

        strcpy(path_file,data);
        if(data[strlen(data)-1] != '/') {
            strcat(path_file,"/");
        }
        strcat(path_file,directory->d_name);

    } while(directory != NULL);
    closedir(dir);

    qsort(array,counter,sizeof(char *),compare);

    for(int k=0;k<counter;k++) {
        struct stat files;
        char ppathh[4096];

        snprintf(ppathh,sizeof(ppathh),"%s/%s",data,array[k]);
        if(stat(ppathh,&files) == -1) {
            perror("Error in stat in JustReveal");
            return;
        }
        colouring(array[k]);
    }
    printf("\n");

    return;
}

void flag_a_Execution(char *data) {
    struct dirent *directory;
    DIR *dir;
    dir = opendir(data);
    int counter = 0;
    char *array[4096];
    char path_file[4096];
    if(dir == NULL) {
        perror("Error in opening the directory in reveal.c in flag_a_execution");
        return;
        // exit(1);
    }
    do {
        directory = readdir(dir);
        if(directory == NULL) {
            break;
        }
        if(counter >= 4096) {
            printf("Too many files");
            break;
        }

        array[counter] = strdup(directory->d_name);
        if(array[counter] == NULL) {
            perror("Error in duplicating in reveal.c in flag_a_execution");
            // exit(1);
            return;
        }
        counter++;

        strcpy(path_file,data);
        if(data[strlen(data)-1] != '/') {
            strcat(path_file,"/");
        }
        strcat(path_file,directory->d_name);
    } while(directory != NULL);
    closedir(dir);

    qsort(array,counter,sizeof(char*),compare);

    for(int i=0;i<counter;i++) {
        struct stat files;
        char ppathh[1024];

        snprintf(ppathh,sizeof(ppathh),"%s/%s",data,array[i]);
        if(stat(ppathh,&files) == -1) {
            perror("Error in stat in flag_a_execution");
            return;
        }
        colouring(array[i]);
    }
    printf("\n");
}

void permissionsRequired(mode_t mode) {
    printf("%c", mode & S_IRUSR ? 'r' : '-');
    printf("%c", mode & S_IWUSR ? 'w' : '-');
    printf("%c", mode & S_IXUSR ? 'x' : '-');
    printf("%c", mode & S_IRGRP ? 'r' : '-');
    printf("%c", mode & S_IWGRP ? 'w' : '-');
    printf("%c", mode & S_IXGRP ? 'x' : '-');
    printf("%c", mode & S_IROTH ? 'r' : '-');
    printf("%c", mode & S_IWOTH ? 'w' : '-');
    printf("%c", mode & S_IXOTH ? 'x' : '-');
    printf("%c", S_ISDIR(mode) ? 'd' : '-');
}

void flag_l_Execution(char *data) {
    struct dirent *directory;
    DIR *dir;
    char path_file[4096];
    dir = opendir(data);

    if(dir == NULL) {
        perror("Error in opening the directory in flag_l_execution");
        // exit(1);
        return;
    }

    char *array[4096];
    int counter = 0;

    do {
        directory = readdir(dir);
        if(directory == NULL) {
            break;
        }

        if(directory->d_name[0] == '.') {
            continue;
        }

        if(counter >= 4096) {
            printf("Too many files");
            break;
        }

        array[counter] = strdup(directory->d_name);
        if(array[counter] == NULL) {
            perror("Error in duplicating in reveal_l_execution");
            // exit(1);
            return;
        }
        counter++;
    } while(directory != NULL);
    closedir(dir);

    qsort(array,counter,sizeof(char*),compare);

    for(int i=0;i<counter;i++) {
        struct stat files;
        char times[128];

        strcpy(path_file,data);
        if(data[strlen(data)-1] != '/') {
            strcat(path_file,"/");
        }     
        strcat(path_file,array[i]);

        if(stat(path_file,&files) == -1) {
            perror("Error in stat in flag_l_execution");
            // exit(1);
            return;
        }
        permissionsRequired(files.st_mode);
        printf("% ld",files.st_nlink);

        struct passwd *PW = getpwuid(files.st_uid);
        struct group *grp = getgrgid(files.st_gid);
        printf(" %s %s",PW->pw_name,grp->gr_name);
        printf(" %5ld",files.st_size);

        strftime(times,sizeof(times), "%b %d:%H:%M",localtime(&(files.st_mtime)));
        printf(" %s ",times);
        colouring(array[i]);
        printf("\n");
    }
}

void flag_al_la_Execution(char *data) {
    struct dirent *directory;
    DIR *dir;
    char path_file[4096];
    char duppath[4096];

    if(strcmp(data,".") == 0 || data == NULL) {
        getcwd(duppath,sizeof(duppath));
    }
    else {
        strncpy(duppath,data,sizeof(duppath)-1);
        duppath[sizeof(duppath)-1] = '\0';
    }
    // dir = opendir(".");
    dir = opendir(duppath);

    if(dir == NULL) {
        perror("Error in opening the directory in flag_al_la_execution");
        // exit(1);
        return;
    }

    char *array[4096];
    int counter = 0;

    do {
        directory = readdir(dir);
        if(directory == NULL) {
            break;
        }

        if(counter >= 4096) {
            printf("Too many files");
            break;
        }

        array[counter] = strdup(directory->d_name);
        if(array[counter] == NULL) {
            perror("Error in duplicating in flag_al_la_execution");
            // exit(1);
            return;
        }
        counter++;
    } while(directory != NULL);
    closedir(dir);

    qsort(array,counter,sizeof(char*),compare);

    for(int i=0;i<counter;i++) {
        struct stat files;
        char times[128];
        strcpy(path_file,data);
        if(data[strlen(data)-1] != '/') {
            strcat(path_file,"/");
        }
        strcat(path_file,array[i]);

        if(stat(path_file,&files) == -1) {
            perror("Error in stat in flag_la_al_execution");
            // exit(1);
            return;
        }
        permissionsRequired(files.st_mode);
        printf("% ld",files.st_nlink);

        struct passwd *PW = getpwuid(files.st_uid);
        struct group *grp = getgrgid(files.st_gid);
        printf(" %s %s",PW->pw_name,grp->gr_name);
        printf(" %5ld",files.st_size);

        strftime(times,sizeof(times), "%b %d:%H:%M",localtime(&(files.st_mtime)));
        printf(" %s ",times);

        colouring(array[i]);
        printf("\n");
        free(array[i]);
    }
}

void reveal_parent(char *data) {
    char path_in_file[4096];
    if(realpath(data,path_in_file) == NULL) {
        perror("error in realpath");
        // exit(1);
        return;
    }
    char *directory_name = dirname(path_in_file);
    JustReveal(directory_name);
}

void reveal_parent_a_flag(char *data) {
    char path_in_file[4096];
    if(realpath(data,path_in_file) == NULL) {
        perror("Error in realpath");
        // exit(1);
        return;
    }
    char *directory_name = dirname(path_in_file);
    flag_a_Execution(directory_name);
}

void reveal_parent_l_flag(char *data) {
    char path_in_file[4096];
    if(realpath(data,path_in_file) == NULL) {
        perror("Error in realpath");
        // exit(1);
        return;
    }
    char *directory_name = dirname(path_in_file);
    flag_l_Execution(directory_name);
}

void reveal_parent_la_al_flag(char *data) {
    char path_in_file[4096];
    if(realpath(data,path_in_file) == NULL) {
        perror("Error in realpath");
        // exit(1);
        return;
    }
    char *directory_name = dirname(path_in_file);
    flag_al_la_Execution(directory_name);
}

void revealFlags(char *input,int flag_a,int flag_l,char *path,char *prepath) {

    if(strcmp(input,"..") == 0) {
        if(flag_a && !flag_l) {
            reveal_parent_a_flag(path);
        }
        else if(flag_l && !flag_a) {
            reveal_parent_l_flag(path);
        }
        else if(flag_a && flag_l) {
            reveal_parent_la_al_flag(path);
        }
        else {
            reveal_parent(path);
        }
        return;
    }
    else if(strcmp(input,".") == 0) {
        if(flag_a && !flag_l) {
        flag_a_Execution(path);
        }
        else if(flag_l && !flag_a) {
            flag_l_Execution(path);
        }   
        else if(flag_a && flag_l) {
            flag_al_la_Execution(path);
        }
        else if(!flag_a && !flag_l) {
            JustReveal(path);
            // return;
        }
        return;
    }
    else if(strcmp(input,"~") == 0) {
        if(flag_a && !flag_l) {
            flag_a_Execution(presentWorkingDirectory);
        }
        else if(flag_l && !flag_a) {
            flag_l_Execution(presentWorkingDirectory);
        }
        else if(flag_a && flag_l) {
            flag_al_la_Execution(presentWorkingDirectory);
        }
        else if(!flag_a && !flag_l) {
            JustReveal(presentWorkingDirectory);
        }
        return;
    }

    if(flag_a && !flag_l) {
        flag_a_Execution(path);
    }
    else if(flag_l && !flag_a) {
        flag_l_Execution(path);
    }   
    else if(flag_a && flag_l) {
        // printf("going\n");
        flag_al_la_Execution(path);
    }
    else if(!flag_a && !flag_l) {
        JustReveal(path);
        // return;
    }
}

void revealExecution(int counter,char *array[],char *data,char *prepath) {
    int flag_a = 0;
    int flag_l = 0;
    char *path = ".";

    for(int i=1;i<counter;i++) {
        if(array[i][0] == '-') {
            for(int j=1;array[i][j] != '\0';j++) {
                if(array[i][j] == 'a') {
                    flag_a = 1;
                }
                else if(array[i][j] == 'l') {
                    flag_l = 1;
                }
            }
        }
        else {
            path = array[i];
        }
    }

    revealFlags(path,flag_a,flag_l,data,prepath);
}
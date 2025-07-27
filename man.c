#include "man.h"

void manPage_execution(char *websiteName,char **array) {
    struct hostent *pageMan = gethostbyname(websiteName);
    if(pageMan == NULL) {
        perror("Error in getting the pageMan by gethostbyname");
        return;
    }
    if(pageMan != NULL) {
        int req_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(req_socket == -1) {
            perror("Error in creating a socket");
            return;
        }
        else if(req_socket != -1) {
            struct sockaddr_in websiteAdd;
            struct in_addr **list = (struct in_addr **)pageMan->h_addr_list;
            websiteAdd.sin_port = htons(80);
            websiteAdd.sin_addr = *list[0];
            websiteAdd.sin_family = AF_INET;

            struct sockaddr *address = (struct sockaddr *)&websiteAdd;
            socklen_t address_len = sizeof(websiteAdd);
            int mutual = connect(req_socket,address,address_len);
            if(mutual == -1) {
                perror("Error in connecting socket");
                return;
            }
            else if(mutual != -1) {
                subManPage(array,req_socket);
            }
        }
    }
}

void subManPage(char **array,int req_socket) {
    char data[4096];
    snprintf(data,sizeof(data),"GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n",array[1]);
    int req = send(req_socket,data,strlen(data),0);
    if(req == -1) {
        perror("Error in sending a request");
        return;
    }
    else if(req != -1) {
        char path[40960];
        int final = recv(req_socket,path,sizeof(path)-1,0);
        if(final < 0) {
            perror("Error in getting the path");
            return;
        }
        else {
            path[final] = '\0';
            char *word = strchr(path,'\n');
            word++;
            int counter = 0;
            do {
                if(word != NULL && counter <= 30) {
                    if(word != NULL) {
                        word++;
                    }
                    else {
                        printf("No such command %s\n",array[1]);
                        return;
                    }

                    if(strncmp(word,"NAME",4) == 0) {
                        break;
                    }
                    word = strchr(word,'\n');
                    counter++;
                }
            } while(word != NULL && counter <= 30);
            if(word == NULL) {
                printf("No such command %s\n",array[1]);
                return;
            }
            if(counter == 31) {
                printf("No such command %s\n",array[1]);
                return;
            }

            char *newword = strchr(word,'\n');
            newword++;

            do {
                if(newword != NULL) {
                    if(newword != NULL) {
                        newword++;
                    }
                    else {
                        break;
                    }
                    if(strncmp(newword,"SEE ALSO",strlen("SEE ALSO")) == 0) {
                        break;
                    }
                    newword = strchr(newword,'\n');

                }
            } while(newword != NULL);

            if(newword != NULL) {
                newword = strchr(newword,'\n');
                newword++;
                newword = strchr(newword,'\n');
                newword++;
                newword = strchr(newword,'\n');
                newword++;
                newword = strchr(newword,'\n');
                newword++;
                
                (*newword) = '\0';
            }
            printf("%s\n",word);
            printf("\n\n\n");
        }
    }
}
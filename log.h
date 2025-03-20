#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define MAX_SIZE 15
#define FILE_PATH "/home/kalakuntlarishika/Desktop/MiniProject-1/log.txt"

void openingFile();
void writeToFile();
void readDataFromFile();
void deletingTheCommands();
void addingTofile(char *input);
void printing_file_data();
void execute_commands_log(int value);

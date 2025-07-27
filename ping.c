#include "ping.h"

int pid_in_ping = -1;    // to track a process that should receive SIGINT when Ctrl+C is pressed
int ctrlC_flag = 0;      // to indicate if Ctrl+C was pressed, though in this version it's not used
int fg_running = 0;
// int returnCode_in_bg_fg;

/* It checks if there's a foreground process (pid_in_ping != -1). If yes, it sends SIGINT to that process. If not, it simply prints a newline and refreshes the shell prompt.*/
void ctrlC_execution() {
    if(pid_in_ping != -1) {
        kill(pid_in_ping,SIGINT);
    }
    else {
        printf("\n");
        displayuserData();
        fflush(stdout);
    }
}

/*If a background process is being tracked (returnCode_in_bg_fg > 0), and it’s not in the foreground (fg_running == 0), it is forcefully killed using SIGKILL. Then the shell prints a logout message and exits safely.*/
void ctrlD_execution() {
    if(returnCode_in_bg_fg > 0 && fg_running == 0) {
        kill(returnCode_in_bg_fg,SIGKILL);
    }
    printf("\nCaught CTRL-D, logging out\n");
    exit(0);
}


void pingExecution(char **array) {
    int pid = atoi(array[1]);
    int signal_given = atoi(array[2]);

    if(kill(pid,0) == -1) {
        perror("No process exists with given pid");
        return;
    }
    if(kill(pid,signal_given) == -1) {
        perror("Error in sending the signal");
        return;
    } 

    printf("Sending signal (%d) to process (pid : %d)\n",signal_given,pid);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//for strlen:
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/* handler for SIGINT */
static void sigint_handler (int signo){
    char buff[20];
    sprintf (buff, "Caught SIGINT!\n");
    puts(buff);
    exit(EXIT_SUCCESS);
    }

int main (void){

    int size = 100;
    char buff1[size];
    for(int i = 0; i < size; i++){
        buff1[i] = '\0';
    }

    char buff0[size];
    for(int i = 0; i < size; i++){
        buff0[i] = '\0';
    }

    int pid = fork();
    
    if(pid == -1){
        sprintf(buff1, "Fork failed.");
        puts(buff1);
    }
    else if(pid == 0){//server
        for (;;) pause ();
        int f = open("z.txt", O_CREAT | O_EXCL );
        if(f == -1){
            sprintf(buff1, "Error in opening exclusively.");
            puts(buff1);
            exit(0);
        }


    }
    else{//client

        if (signal (SIGINT, sigint_handler) == SIG_ERR) {
            char buff1[20];
            sprintf (buff1, "Cannot handle SIGINT!\n");
            puts(buff1);
            exit(EXIT_FAILURE);
        }

        int input = read(0, buff0, 2);
        if(input == -1){
            perror("In taking input:");
        }
        int f = open("z.txt", O_CREAT);
        for (;;) pause ();

        
    }
    return 0;
}
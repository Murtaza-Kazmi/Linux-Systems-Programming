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
    // exit(EXIT_SUCCESS);
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

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
            char buff1[30];
            sprintf (buff1, "Cannot handle SIGINT!\n");
            puts(buff1);
            exit(EXIT_FAILURE);
        }

    int pid = fork();
    
    if(pid == -1){
        sprintf(buff1, "Fork failed.");
        puts(buff1);
    }
    else if(pid == 0){//server

        pause ();
        sprintf (buff1, "Server: signal received\n");
        puts(buff1);

        //opens file
        int f = open("z.txt", O_RDONLY | O_CREAT | O_EXCL );
        if(f == -1){
            perror("In opening file in server excl.");
            exit(0);
        }
        
        //reads from file
        int input = read(f, buff0, 2);
        if(input == -1){
            perror("Server: In taking input");
            exit(0);
        }

        //calculates sum
        int res = 0;
        for(int i = 0; i < strlen(buff0); i++){
            res += (int) buff0[i];
        }

        sprintf(buff1, "%d", res);
        
        //opens file
        f = open("z.txt", O_WRONLY | O_CREAT | O_APPEND );
        if(f == -1){
            perror("In opening file in server excl.");
            exit(0);
        }

        //writes sum to file
        if(write(f,buff1, 2) == -1){
            perror("In writing to file in client");
            exit(0);
        }

        //sends signal to child
        int sigRes = kill(pid, SIGUSR1);
        if(sigRes == -1){
            perror("In error handling");
            exit(0);
        }
        sprintf (buff1, "Server: signal sent\n");
        puts(buff1);

    }
    else{//client

        //takes input
        int input = read(0, buff0, 2);
        if(input == -1){
            perror("In taking input");
            exit(0);
        }

        //writes to file
        int f = open("z.txt", O_WRONLY | O_CREAT, S_IRWXU);
        if(f == -1){
            perror("In opening file in client");
            exit(0);
        }

        int res = write(f,buff0, 2);
        if(res == -1){
            perror("In writing to file in client");
            exit(0);
        }

        //sends signal to child
        int sigRes = kill(pid, SIGUSR1);
        if(sigRes == -1){
            perror("In error handling");
            exit(0);
        }
        sprintf (buff1, "Client: signal sent\n");
        puts(buff1);

        //gets blocked until child sends signal
        pause();
        sprintf (buff1, "Client: signal received\n");
        puts(buff1);

        //reads result from file
        f = open("z.txt", O_RDONLY | O_CREAT);
        if(f == -1){
            perror("In opening file in client");
            exit(0);
        }

        int output = read(f, buff0, 2);
        if(output == -1){
            perror("In reading program output");
            exit(0);
        }

        //prints result
        puts(buff0);

        
    }
    return 0;
}
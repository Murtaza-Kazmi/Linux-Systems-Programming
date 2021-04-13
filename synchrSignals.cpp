//This program adds the first two digits entered by user and prints the result.

//for open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//for strlen:
#include <string.h>

//for signals
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //main API header file
#include <signal.h>

/* handler for SIGINT */
  static void sigint_handler (int signo){
    char buff[20];
    sprintf (buff, "Caught SIGINT!");
    puts(buff);
    }
const union sigval x {
    // int   sival_int = 0;
    // void *sival_ptr;
};

int main(void){

    int size = 100;
    char buff1[size];
    for(int i = 0; i < size; i++){
        buff1[i] = '\0';
    }

    char buff0[size];
    for(int i = 0; i < size; i++){
        buff0[i] = '\0';
    }

    struct sigaction sa;
    sa.sa_handler = &sigint_handler;
    
    // if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
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

        pause();
        
        sprintf (buff1, "Server: signal received.");
        puts(buff1);

        //opens file
        int f = open("z.txt", O_RDONLY | O_CREAT );
        if(f == -1){
            perror("In opening file in server excl.");
            exit(EXIT_FAILURE);
        }
        
        //reads from file
        int input = read(f, buff0, 2);
        if(input == -1){
            perror("Server: In taking input");
            exit(EXIT_SUCCESS);
        }

        //calculates sum
        int res = 0;
        for(int i = 0; i < strlen(buff0); i++){
            res += (int) buff0[i] - '0';
        }

        sprintf(buff1, "%d", res);
        
        //opens file
        f = open("z.txt", O_WRONLY | O_TRUNC | O_APPEND );
        if(f == -1){
            perror("In opening file in server excl.");
            exit(EXIT_FAILURE);
        }

        //writes sum to file
        if(write(f,buff1, 2) == -1){
            perror("In writing to file in client");
            exit(EXIT_SUCCESS);
        }

        //sends signal to child
        int sigRes = sigqueue(getppid(), SIGUSR1, x);
        // int sigRes = kill(getppid(), SIGUSR1);
        if(sigRes == -1){
            perror("In error handling");
            exit(EXIT_FAILURE);
        }
        sprintf (buff1, "Server: signal sent");
        puts(buff1);

    }
    else{//client

        //takes input
        int input = read(0, buff0, 2);
        if(input == -1){
            perror("In taking input");
            exit(EXIT_SUCCESS);
        }

        //writes to file
        int f = open("z.txt", O_WRONLY | O_CREAT, S_IRWXU);
        if(f == -1){
            perror("In opening file in client");
            exit(EXIT_FAILURE);
        }

        int res = write(f,buff0, 2);
        if(res == -1){
            perror("In writing to file in client");
            exit(EXIT_FAILURE);
        }

        //sends signal to child
        int sigRes = sigqueue(pid, SIGUSR1, x);
        // int sigRes = kill(pid, SIGUSR1);
        if(sigRes == -1){
            perror("In error handling");
            exit(EXIT_FAILURE);
        }
        sprintf (buff1, "Client: signal sent");
        puts(buff1);

        //gets blocked until child sends signal
        pause();
        sprintf (buff1, "Client: signal received");
        puts(buff1);

        //reads result from file
        f = open("z.txt", O_RDONLY | O_CREAT);
        if(f == -1){
            perror("In opening file in client");
            exit(EXIT_FAILURE);
        }

        int output = read(f, buff0, 10);
        if(output == -1){
            perror("In reading program output");
            exit(EXIT_FAILURE);
        }

        //prints result
        puts(buff0);

    }
    return 0;
}
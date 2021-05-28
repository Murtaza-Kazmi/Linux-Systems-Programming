/*
 Copyright (c) 1986 Regents of the University of California.
 All rights reserved.  The Berkeley software License Agreement
 specifies the terms and conditions for redistribution.

	@(#)streamwrite.c	6.2 (Berkeley) 5/8/86
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <list>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

using namespace std;


#define DATA "Half a league, half a league . . ."

struct AllProcess{

    int PID;
    string name;
    int status;
    double starttime;
    double endtime;
    double elapsedtime;

};
AllProcess processes[20];
static int count1 = 0;
static int killpid = 0;

void *print_r_function(void *ptr);
void *print_rw_function(void *ptr);
static int sock;


/*
 * This program creates a socket and initiates a connection with the socket
 * given in the command line.  One message is sent over the connection and
 * then the socket is closed, ending the connection. The form of the command
 * line is streamwrite hostname portnumber
 */

int main(int argc, char *argv[])
	{
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[1024];
	void printing(int sum[], int er[]);
    bool checkvalid(char* t);
    char u[100];
    double sum = 0;
    int sum1[20];
    int er[20];
    int en = 0;
    bool flag = false;
    int colon = 0;
    int num = 0;
    int dl = 0;
    char str[20];


    //printf("%s\n", "Starting ");
    int fd[2];
    int fd1[2];
    int n = pipe(fd);
    int m = pipe(fd1);
    char ending[20];
    char s[20];
    char p[20];
    char c[20];
    int a = 0;
    int ipc = 0;
    int count1 = 0;
    char* h = str;

    list <AllProcess> t1;










	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(1);
	}
	/* Connect socket using name specified by command line. */
	server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);
	if (hp == 0) {
		fprintf(stderr, "%s: unknown host\n", argv[1]);
		exit(2);
	}
	bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
	server.sin_port = htons(atoi(argv[2]));

	if (connect(sock,(struct sockaddr *) &server,sizeof(server)) < 0) {
		perror("connecting stream socket");
		exit(1);
	}
	while(true) {


       pthread_t thread1, thread2;
     const char *message1 = "Thread 1";
     const char *message2 = "Thread 2";
     int  iret1, iret2;

    int res1, res2, err;
    pthread_attr_t attr;
    pthread_attr_t attr2;

    res1 = pthread_attr_init(&attr);
    if (res1 != 0) {
        perror("Attribute init failed");
        exit(EXIT_FAILURE);
    }

    res1 = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (res1 != 0) {
        perror("Setting detached state failed");
        exit(EXIT_FAILURE);
    }

    res1 = pthread_create(&thread1, &attr, print_r_function, (void*) message1);
    if (res1 != 0) {
        //write(STDOUT_FILENO, "1", 1);
        perror("Creation of thread failed");
        exit(EXIT_FAILURE);
    }

    res2 = pthread_attr_init(&attr2);
    if (res2 != 0) {
        perror("Attribute init failed");
        exit(EXIT_FAILURE);
    }
    res2 = pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_DETACHED);
    if (res2 != 0) {
        perror("Setting detached state failed");
        exit(EXIT_FAILURE);
    }

    res2 = pthread_create(&thread2, &attr2, print_rw_function, (void*) message2);
    if (res2 != 0) {
        perror("Creation of thread failed");
        exit(EXIT_FAILURE);
    }


    printf("Child thread finished.\n");
    pthread_attr_destroy(&attr);
    pthread_attr_destroy(&attr2);

     //exit(EXIT_SUCCESS);



		//write(STDOUT_FILENO, "second\n", 6);


        //getchar();

    }
	close(sock);
}


bool checkvalid(char* t){
        bool invalid = false;
        while(*t != '\0'){
            char c = *t;
            //if ascii is 10, that means new line and then break the loop
            if ((int)c == 10){
                break;
            }
            //checking ascii for the character not an integer or equal to ';' or '+' or '-', then the char is invalid
            if (((int)c < 48 || (int)c > 57) && (int)c != 59 && (int)c != 45 && (int)c != 43){
                invalid = true;
            }
            t++;
        }
        return invalid;
    }

void *print_rw_function(void *ptr)
{
    char str[20];
    write(STDOUT_FILENO, "Enter a list of words for add, sub, mult, div like e.g. add 22 22 will give result of 44. Don't give space aftering entering last command \nFor running a program, enter e.g. run firefox \nFor ending the program enter 'end program' \n", sizeof("Enter a list of words for add, sub, mult, div like e.g. add 22 22 will give result of 44. Don't give space aftering entering last command \nFor running a program, enter e.g. run firefox \nFor ending the program enter 'end program' \n"));
    read(STDIN_FILENO, str, 25);
    if (write(sock, str, sizeof(str)) < 0)
		perror("writing on stream socket");
     //printf("%s \n", message);
}


void *print_r_function(void *ptr)
{
        char read1[20];
        int n6 = read(sock, read1, 20);



        if (strcmp(read1, "Close Program") == 0){
            write(STDOUT_FILENO, "Client is closed\n", 17);
        }

        else {
        write(STDOUT_FILENO, read1, n6);
        write(STDOUT_FILENO, "\n", 1);
        }

}
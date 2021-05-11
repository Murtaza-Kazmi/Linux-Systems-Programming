#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

//for socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

//for strlen:
#include <cstring>

//for sprintf
#include <string>

//for signals
#include <stdlib.h>
#include <stdio.h>
//+ main API header file
#include <signal.h>

//therad
#include <pthread.h>

void *read_function( void *ptr );
void *write_function( void *ptr );
void handler (int signo);

int size = 10000;


int main(int argc, char *argv[]){


	struct sigaction sa;
    sa.sa_handler = handler;

	if (sigaction(SIGPIPE, &sa, 0) == -1) {
		char buff1[30];
		sprintf (buff1, "Cannot handle SIGPIPE!\n");
		puts(buff1);
		exit(EXIT_FAILURE);
	}


	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[1024];

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

	int size = 10000;
	
	pthread_t thread1, thread2;
    const int *s = &sock;
    int  iret1, iret2;

    iret1 = pthread_create( &thread1, NULL, read_function, (void*) s);

    if(iret1){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create( &thread2, NULL, write_function, (void*) s);

    if(iret2){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        exit(EXIT_FAILURE);
    }

    printf("pthread_create() for thread 1 returns: %d\n",iret1);
    printf("pthread_create() for thread 2 returns: %d\n",iret2);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
	close(sock);
	exit(0);
}


void *read_function( void *s ){
	//buffer used for read 	
	char buff0[10000];

	int *sockp = (int *) s;
	int sock = *sockp;

	//buffer used for sprintf 	
	char buff1[10000];
	while(true){
		int readResponseResult = read(sock, buff0, sizeof(buff0)-1);

		if(readResponseResult == 0){
			sprintf(buff1, "Connection broke.");
			puts(buff1);
			exit(0);
		}
		
		puts(buff0);
	}
}

void *write_function(void *s){
	int *sockp = (int *) s;
	int sock = *sockp;
	while(true){

		//buffer used for read 	
		char buff0[10000];

		//buffer used for sprintf 	
		char buff1[10000];

		for(int i = 0; i < size; i++){
			buff0[i] = '\0';
			buff1[i] = '\0';
		}

		//reads until enter, so no garbage value, truncates until character
		int noOfBytesRead = read(0, buff0, size-1);
		
		if(buff0[0] == '\n'){
			sprintf(buff1, "Invalid number of arguments. Please enter again.");
			puts(buff1);
			continue;
		}

		if(noOfBytesRead == -1){
			perror(("Error in read."));
		}
		
		// send input to server (sends the bytes inputted)
		int writeResult = write(sock, buff0, noOfBytesRead-1);
		if(writeResult < 0){
			perror("Error in writing from server to client.");
		}
	}
}

void handler (int signo){
	if(signo == SIGCHLD){
		char buff[1000] = "Caught SIGPIPE. So connection with server is lost.\n";
		write(1, buff, strlen(buff));
		exit(0);
	}
}

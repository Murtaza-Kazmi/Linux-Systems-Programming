#include <unistd.h>
#include <stdlib.h>
#include <strings.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

//for strlen:
#include <cstring>

//for sprintf
#include <string>

int main(int argc, char *argv[]){
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

	while(true){

		//buffer used for read 	
		char buff0[size];

		//buffer used for sprintf 	
		char buff1[size];

		for(int i = 0; i < size; i++){
			buff0[i] = '\n';
			buff1[i] = '\n';
		}

		//reads until enter, so no garbage value
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

		int readResponseResult = read(sock, buff0, sizeof(buff0)-1);

		if(readResponseResult < 0){
			perror("Client: error in reading response sent by server.");
		}

		sprintf(buff1, "%s", buff0);
		// sprintf(buff1, "1 ");
		if(strcmp(buff1, "Exit!") == 0){
			sprintf(buff1, "Terminated.");
			puts(buff1);
			exit(1);
		}
		else{
		puts(buff1);
		}
		
		//while ends
	}
	close(sock);
}

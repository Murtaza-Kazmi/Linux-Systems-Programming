 // preprocessor directives -------------------------------------------------------------------------------

//for sprintf
 #include <string>

//for strcmp, strtok
#include <cstring>

// for system calls: pipe(), exec()
#include <unistd.h>

//for close-on-exec: O_CLOEXEC (read man pipe2)      
#include <fcntl.h>              

//for time
#include <ctime>

//for kill()
#define SIGTERM 15

//for waitpid
#include <sys/types.h>
#include <sys/wait.h>

//for signals
#include <stdlib.h>
#include <stdio.h>
//+ main API header file
#include <signal.h>
 
//missing headers
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>


//socket headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#define TRUE 1

  


class Process {       
        public:            
            char name[100];
            int pid;
            char status[10];
            time_t startTime;
};

class Client {       
        public:           
            int pid;
};

int noOfProcessesAllowed = 100;
Process processes[100];
Client clients[100];
int processIndex = 0;
int clientsIndex = 0;
int size = 10000;
int sock;
int indexOfAcceptedClients = -1;

//check 
int msgsock;//used in handler


void spawnProcess(int sock, bool callAccept, int pid){
	int msgsock;
	if(callAccept){
		msgsock = accept(sock, 0, 0);
		indexOfAcceptedClients++;
		if (msgsock == -1){
			perror("accept");
		exit(EXIT_FAILURE);
		}
		char buff[100];
		sprintf(buff, "Accepted new client.");
		puts(buff);
		clients[clientsIndex].pid = pid;
		clientsIndex += 1;
	}
	else{
		msgsock = sock;
	}
	
	do {
		
		int responseAttempt;
		int argc;
		char* argv[size];

		//buffer used for read 	
		char buff0[size];

		//buffer used for sprintf 	
		char buff1[size];

		//there could be garbage values in buff0
		for(int i = 0; i < size; i++){
			buff0[i] = '\0';
			buff1[i] = '\0';
		}

		int readResult = read(msgsock,  buff0, sizeof(buff0)-1);

		if(readResult < 0){
			sprintf(buff1, "Server: error in reading from msgsock of client.");
			responseAttempt = write(msgsock, buff1, strlen(buff1)-1);
			sprintf(buff0, "Wrote this to client: %s", buff1);
			puts(buff0);
			continue;
		}
		if(readResult == 0){
			sprintf(buff1, "\nClient Handler: I am terminating.");
			puts(buff1);
			exit(1);
		}

		sprintf(buff1, "Received this from client: %s", buff0);
		puts(buff1);

		//adds input delimited by single space to argv array
		char* token = strtok(buff0, " ");
		int ind = 0;
		while(token != NULL) {
			
			argv[ind] = token;
			ind += 1;
			token = strtok(NULL, " "); 
			
		}

		// arg count:
		argc = ind;
		char* requirement = argv[0];

		if(argc == 1){
			if(strcmp(requirement, "list") == 0){
				
				if(processIndex == 0){
					sprintf(buff1, "Please initiate a process first.");
				}
				else{
					time_t curTime = time(NULL);
					sprintf(buff1, " ");

					bool flag = false;

					for(int i = 0; i < processIndex; i++){
						time_t elapsedTime = curTime - processes[i].startTime;
						if(strcmp(processes[i].status, "active") == 0){
							flag = true;
							sprintf(buff1, "%s\nIndex: %d              Name: %s             pID: %d          Start Time: %time_t          Elapsed Time: %time_t             Status:%s", buff1, i, processes[i].name, processes[i].pid, processes[i].startTime, elapsedTime, processes[i].status);
						}
					}
					sprintf(buff1, "\n%s\nNote: me_t = seconds.", buff1);
					if(!flag){
						sprintf(buff1, "No active process.");
					}
				}
			
		}
			else{
				sprintf(buff1, "Invalid requirements. Please re-enter.");
			}

			responseAttempt = write(msgsock, buff1, strlen(buff1)-1);
			sprintf(buff0, "Wrote this to client: %s", buff1);
			puts(buff0);
			continue;
		}
		
		char* requirement2 = argv[1];


		if(strcmp(requirement, "add") == 0){ 

			int total = 0;
			bool canAdd = true;
			//used to calculate length
			char* current;
			
			
			// for loop begins ----------------------------
			for(int i = 1; i < argc; i++){
				canAdd = true;
				current = argv[i];

				for(int j = 0; j < strlen(current); j++){
					if(!isdigit(argv[i][j])){
						canAdd = false;
						break;
					}
				}
				if(canAdd){
					total += atoi(argv[i]);
				}
				else{
					break;
				}
			}
			// for loop ended ----------------------------

			if(canAdd){
				sprintf(buff1, "The total is: %d.", total); 
			}
			else{
				sprintf(buff1, "Invalid input. Please enter valid numbers only.");
			}
		}
		else if(strcmp(requirement, "sub") == 0){

			int total = 0;
			bool canAdd = true;
			char* current;
			// for loop begins ----------------------------
			for(int i = 1; i < argc; i++){
				canAdd = true;
				current = argv[i];
				
				for(int j = 0; j < strlen(current); j++){
					if(!isdigit(argv[i][j])){
						canAdd = false;
						break;
					}
				}
				if(canAdd){
					if(i == 1) total += atoi(argv[i]);
					else total -= atoi(argv[i]);
				}
				else{
					break;
				}
			}
			// for loop ended ----------------------------

			if(canAdd){
				sprintf(buff1, "The total is: %d.", total);
			}
			else{
				sprintf(buff1, "Invalid input. Please enter valid numbers only.");
			}
		}
		else if(strcmp(requirement, "mul") == 0){

			int total = 1;
			bool canAdd = true;
			char* current;
			// for loop begins ----------------------------
			for(int i = 1; i < argc; i++){
				canAdd = true;
				current = argv[i];
				for(int j = 0; j < strlen(current); j++){
					if(!isdigit(argv[i][j])){
						canAdd = false;
						break;
					}
				}
				if(canAdd){
					total = total * atoi(argv[i]);
				}
				else{
					break;
				}
			}
			// for loop ended ----------------------------

			if(canAdd){
				sprintf(buff1, "The total is: %d.", total);
			}
			else{
				sprintf(buff1, "Invalid input. Please enter valid numbers only.");
			}
		}
		else if(strcmp(requirement, "div") == 0){
			float total = 1;
			bool canAdd = true;
			char* current;
			// for loop begins ----------------------------
			for(int i = 1; i < argc; i++){
				canAdd = true;
				current = argv[i];
				for(int j = 0; j < strlen(current); j++){
					if(!isdigit(argv[i][j])){
						canAdd = false;
						break;
					}
				}
				//is an integer
				if(canAdd){
						if(i == 1 && argv[i] == 0) total = 0;
						else if(i == 1) total = atoi(argv[i]);
						else if(total == 0.0){
							total = 0;
						}
						else if(atoi(argv[i]) == 0){
							canAdd = false;
							break;
						}
						else total = total/atoi(argv[i]);
					
				}
				else{
					break;
				}
			}
			// for loop ended ----------------------------

			if(canAdd){
				sprintf(buff1, "The total is: %f.", total);
			}
			else{
				sprintf(buff1, "Invalid input. Please enter valid numbers only.");
			}
		}
		else if(strcmp(requirement, "run") == 0){ // -------------------------------------------------------------- RUN -------------------------------------------------------------------------------------------
			
			char* current = argv[1];

			int l = strlen(current);

			char name[l+1];

			for(int i = 0; i < l; i++){
				name[i] = argv[1][i];
			}
			name[l] = '\0';

			int fdServerChildToServer[2];

			int pipeRes = pipe2(fdServerChildToServer, O_CLOEXEC);
			
			if(pipeRes < 0){
				sprintf(buff1, "Server: error in initiating pipe.");
			}

			else{
				
				int newPID = fork();

				if(newPID < 0){
					sprintf(buff1, "Server: error in fork before execution.");
				}
				else if(newPID == 0){ // child
										
					// call exec

					sprintf(buff1, "%s", name);
					int execResult = execlp(buff1, buff1, "-s", NULL);

					write(fdServerChildToServer[1], "failure", 10);

					//terminate this process
					exit(1);
				}
				else{//parent - keep it running
					
					close(fdServerChildToServer[1]);
					int res = read(fdServerChildToServer[0],  buff0, 10);
					// sprintf(buff1, "%d", res);
					// puts(buff1);
					if(res == 0){//success
							for(int i = 0; i < strlen(name); i++){
							processes[processIndex].name[i] = name[i];
						}
						processes[processIndex].name[strlen(name)] = '\0';
						processes[processIndex].startTime = time(NULL);
						processes[processIndex].pid = newPID;
						char temp[9] = "active"; //9 so that inactive is assignable
						for(int i = 0; i < strlen("active"); i++){
							processes[processIndex].status[i] = temp[i];
						}
						processes[processIndex].status[strlen("active")] = '\0';
						
						processIndex += 1;
						sprintf(buff1, "Success.");
					}
					else{//exec has failed
						sprintf(buff1, "exec() failed.");
					}
			}
			}
			
			//run ends   
		}

		else if((strcmp(requirement, "list") == 0) && (strcmp(requirement2, "all") == 0)){
			if(processIndex == 0){
				sprintf(buff1, "Please initiate a process first.");
			}
			else{
			time_t curTime = time(NULL);
			sprintf(buff1, " ");
			for(int i = 0; i < processIndex; i++){
				time_t elapsedTime = curTime - processes[i].startTime;
				sprintf(buff1, "%s\nIndex: %d              Name: %s             pID: %d          Start Time: %time_t          Elapsed Time: %time_t             Status:%s", buff1, i, processes[i].name, processes[i].pid, processes[i].startTime, elapsedTime, processes[i].status);
			}
			sprintf(buff1, "\n%s\nNote: me_t = seconds.", buff1);
			}
		}

		else if(strcmp(requirement, "kill") == 0){// -------------------------------------------------------------- KILL -------------------------------------------------------------------------------------------
			
			bool isID = true;
			bool isName = true;
			
			for(int i = 0; i < strlen(requirement2); i++){
				if(!isdigit(requirement2[i])){
					isID = false;
				}
				if(isdigit(requirement2[i])){
					isName = false;
				}
			}
			if(!isName && !isID){
				sprintf(buff1, "Invalid id and/or name.");
			}
			else{
				bool success = true;
				bool inList = false;
				bool flag = true;

				if(isName){
					for(int i = 0; i < processIndex; i++){
						if((strcmp(processes[i].name, requirement2) == 0) && (strcmp(processes[i].status, "active") == 0)){
							inList = true;
							int res = kill(processes[i].pid, SIGKILL);
							sprintf(buff1, "Ran kill on %d. Kill res = %d", processes[i].pid, res);
							puts(buff1);

							if(res == 0){//mark inactive
								char temp[9] = "inactive";
								for(int j = 0; j < strlen("inactive"); j++){
									processes[i].status[j] = temp[j];
								}
								processes[i].status[strlen("inactive")] = '\0';
								}
							else{
								sprintf(buff1, "Error in kill");
								puts(buff1);
								success = false;
							}
						}
					}
				}
				else{
					for(int i = 0; i < processIndex; i++){
						if(processes[i].pid == atoi(requirement2) && (strcmp(processes[i].status, "active") == 0)){
						
							inList = true;
							int res = kill(processes[i].pid, SIGKILL);
							sprintf(buff1, "Ran kill on %d. Kill res = %d", processes[i].pid, res);
							puts(buff1);

							if(res == 0){ //mark inactive
								char temp[9] = "inactive";
								for(int j = 0; j < strlen("inactive"); j++){
									processes[i].status[j] = temp[j];
								}
								processes[i].status[strlen("inactive")] = '\0';
								}
							else{
								sprintf(buff1, "Error in kill");
								success = false;
							}
						}
					}

				}
				if(success && inList){
					sprintf(buff1, "Done killing.");
				}
				else{
					if(flag){
					sprintf(buff1, "Invalid id and/or name.");
					}
				}
			}
			
		}
		
		else{
			sprintf(buff1, "Invalid requirement. Please re-enter.");
		}

		responseAttempt = write(msgsock, buff1, strlen(buff1)-1);
		sprintf(buff0, "Wrote this to client: %s", buff1);
		puts(buff0);
		
	} while (true);
	close(msgsock);
	exit(1);
}


void handler (int signo){
	if(signo == SIGCHLD){

		int id = getpid();
		char buff[1000] = "\nCaught SIGCHILD.\n";
		sprintf(buff, "%s In process with pID: %d", buff, id);
		puts(buff);

		int terminatedProcessID = waitpid(-1, NULL, WNOHANG);

		for(int i = 0; i < 100; i++){
			if(processes[i].pid == terminatedProcessID){
				//mark inactive
				sprintf(buff, "\nCollected pid of application %s with PID = %d", processes[i].name, processes[i].pid);
				puts(buff);
				char temp[9] = "inactive";
				for(int j = 0; j < strlen("inactive"); j++){
					processes[i].status[j] = temp[j];
				}
				processes[i].status[strlen("inactive")] = '\0';
			}
			if(clients[i].pid == terminatedProcessID){
				//unable to reach here since list not updated, so EITHER update the list through updateActivated() OR loop until -1
				//with pid = 0 since not immediate child!
				sprintf(buff, "Collected pid of client handler. Index = %d. PID = %d\n Updated client handlers list is as follows:", i, clients[i].pid);
				puts(buff);


				sprintf(buff, "\0");
				clients[i].pid = -1;
				for(int j = 0; j < clientsIndex; j++){
					sprintf(buff, "%s\nIndex: %d PID: %d", buff, j, clients[j].pid);
				}
				puts(buff);
				
				bool callAccept = true;
				sprintf(buff, "Spawning in handler.");
				puts(buff);
				int forkRes = fork();
				if(forkRes == 0){
					spawnProcess(sock, callAccept, 0);
				}
				else if(forkRes < 0){
					perror("fork() in handler.");
				}
				else{
					indexOfAcceptedClients++;
					clients[clientsIndex].pid = forkRes;
					clientsIndex += 1;
				}
			}
		}

	}
	//check
	else if(signo == SIGINT){
		int id = getpid();
		char buff[1000] = "Caught SIGINT. Closing sock and msgsock";
		sprintf(buff, "%s in %d.\n", buff, id);
		write(1, buff, strlen(buff));
		close(msgsock);
		close(sock);
		exit(1);
	}
}

void displayClientCommunicators(){
	char buff[1000];
	sprintf(buff, " ");
	for(int j = 0; j < clientsIndex; j++){
		sprintf(buff, "%s\nIndex: %d PID: %d", buff, j, clients[j].pid);
	}
	puts(buff);
	char duff[10];
	sprintf(duff, "--------");
	puts(duff);
}

void *server_client_handler(void *arg){
	char buff[100];
	while (true)
	{
		for(int i = 0; i < 100; i++){
			buff[i] = '\0';
		}

		int readRes = read(0, buff, sizeof(buff));
		
		if(strcmp(buff, "conn list\n") == 0){
			sprintf(buff, " ");
			// for(int j = 0; j < clientsIndex; j++){
			// 	sprintf(buff, "%s\nIndex: %d PID: %d", buff, j, clients[j].pid);
			// }
			// puts(buff);
			displayClientCommunicators();
		}
		else if(strcmp(buff, "list\n") == 0){
			exit(0);
		}
		else if(strcmp(buff, "exit\n") == 0){
			exit(0);
		}
		else{
			sprintf(buff, "Invalid requirement.");
			puts(buff);
		}
	}
}

void updateActivated(){
	//communicates with clientCommunicators and if any of them is activated, the main server process is updated with the list
	//if not used, only the children accepted in the main server process would be updated.

	//right only sigchild of unupdates clients is generated, not caught by parent
}


// main ----------------------------------------------------------------------------------------------------------------------------------------------------
//call

int main(void){
	//signal initialization --------------


	struct sigaction sa;
    sa.sa_handler = handler; 
	// SA_NODEFER to catch the same signal as the one currently handling
	// SA_NORESART to restart interrupted API calls
	sa.sa_flags = SA_NODEFER | SA_RESTART;

	if (sigaction(SIGCHLD, &sa, 0) == -1) {
            char buff1[30];
            sprintf (buff1, "Cannot handle SIGCHLD!\n");
            puts(buff1);
            exit(EXIT_FAILURE);
        }
		//check
	struct sigaction sa2;
    sa2.sa_handler = handler; 
	sa2.sa_flags = SA_NODEFER;
	if (sigaction(SIGINT, &sa2, 0) == -1) {
            char buff1[30];
            sprintf (buff1, "Cannot handle SIGINT!\n");
            puts(buff1);
            exit(EXIT_FAILURE);
        }
 

	int length;
	struct sockaddr_in server;
	char buf[1024];
	int rval;
	int i;

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(1);
	}
	/* Name socket using wildcards */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(55001);
	if (bind(sock, (struct sockaddr *) &server, sizeof(server))) {
		perror("binding stream socket");
		server.sin_port = htons(55001);
		if (bind(sock, (struct sockaddr *) &server, sizeof(server))) {
			server.sin_port = htons(55002);
			if (bind(sock, (struct sockaddr *) &server, sizeof(server))){
				exit(0);
			}
		}
	}
	/* Find out assigned port number and print it out */
	length = sizeof(server);
	if (getsockname(sock, (struct sockaddr *) &server, (socklen_t*) &length)) {
		perror("getting socket name");
		exit(1);
	}
	printf("Socket has port #%d\n", ntohs(server.sin_port));
	fflush(stdout);

	/* Start accepting connections */
	listen(sock, 10);

	int maxNoOfForks = 4;
	int forkCount = 0;
	int forkRes;
	bool callAccept;

	pthread_t thread1;
    const int *s = &sock;
    int  iret1;

    iret1 = pthread_create( &thread1, NULL, server_client_handler, (void*) sock);

    if(iret1){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

	while(true){
		
		if(forkCount < maxNoOfForks){

			forkRes = fork();
			// forkRes = fork();
			if(forkRes > 0){
				clients[clientsIndex].pid = forkRes;
				clientsIndex++;
				forkCount++;
				continue;
			}
			else if(forkRes == 0){
					callAccept = true;
					spawnProcess(sock, callAccept, forkRes);
			}
			else{
				perror("fork()");
			}
		}
		else{
			char buff[100];

			msgsock = accept(sock, 0, 0);

			forkRes = fork();

			indexOfAcceptedClients++;
			clients[clientsIndex].pid = forkRes;
			clientsIndex += 1;
			
			if(forkRes > 0){
				continue;
			}
			else if(forkRes == 0){
				callAccept = false;
				sprintf(buff, "Accepted new client before fork().");
				puts(buff);
				spawnProcess(msgsock, callAccept, forkRes);
			}
			else{
				perror("fork() in main()");				
			}
		}
		displayClientCommunicators();
	}
	close(sock);
}
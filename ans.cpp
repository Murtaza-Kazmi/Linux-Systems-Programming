
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

// for inet_aton(), inet_addr() and inet_ntoa()
#include<arpa/inet.h> 

// for multiplexed I/O
#include <poll.h>

void handler(int signo){

    int fd = open("f.txt", O_RDONLY, S_IRWXU);
    char buff[100];
    for(int i = 0; i < 100; i++){
        buff[i] = '\0';
    }

    read(fd, buff, 14);
    
    write(1, buff, strlen(buff));
    exit(1);
}

int main(){

    char buff[100];
    for(int i = 0; i < 100; i++){
        buff[i] = '\0';
    }
    int res;

    int f = fork();
    if(f == 0){
        
        res = read(0, buff, 50);
        char *token = strtok(buff, " ");
		int ind = 0;
        int argv[2];
		while(token != NULL) {
			argv[ind] = atoi(token);
			ind += 1;
			token = strtok(NULL, " ");
		}

        int ans = argv[0] + argv[1];

        int fd = open("f.txt", O_CREAT | O_WRONLY, S_IRWXU);

        sprintf(buff, "The sum is: %d ", ans);
        write(fd, buff, strlen(buff));
        exit(EXIT_SUCCESS);
    }
    else if(f > 0){
        struct sigaction h;
        h.sa_handler = handler;
	    h.sa_flags = SA_NODEFER | SA_RESTART;
	    sigaction(SIGCHLD, &h, 0);
        while(true){
            continue;
        }
    }
    else{

    }
    return 0;
}
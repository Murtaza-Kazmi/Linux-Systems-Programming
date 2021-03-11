//for fork
#include <unistd.h>
#include <sys/types.h>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//sprintf
#include <stdio.h>

//string for strtok
//iostream for stoi
#include <iostream>
#include <string.h>

using namespace std;

//the program takes two integer digits separate by single space as input
//in parent process, and the child process prints their addition.
int main(){
		
	int fds[2];
	int pipeResult = pipe(fds);
	if(pipeResult < 0){
		perror("Pipe");
	}
	
	int pid = fork();
	
	if(pid > 0){
		
	char arr[3];
	
	int readResult = read(0, arr, 3);
	if(readResult < 0){
		perror("Parent: Error in read");
	}
	
	int writeResult = write(fds[1], arr, 3);
	if(writeResult < 0){
		perror("Parent: Error in write");
	}
	}
	
	else if (pid == 0){
		
	char arr2[3];
	int readResultChild = read(fds[0], arr2, 3);
	
	char* token = strtok(arr2, " ");

	int total = 0;
	
	while(token != NULL) {
		
		total += stoi(token);
		token = strtok(NULL, " "); 
		
	}
	
	printf("%d \n", total);
	
	//if (write(1, arr2, 3) == -1) perror("Child: Error in write");
	
	
		
	}

	else{
		perror("Fork failed in source code");
	}





	return 0;
}
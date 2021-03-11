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

//to string
#include <string> 


using namespace std;

// Two-way communication
//reads number in parent
//adds in child
//prints result in parent
int main(){
		
	int fds[2];
	int fds2[2];
	
	int pipeResult = pipe(fds);
	int pipeResult2 = pipe(fds2);
	
	// -------------------------------------- PARENT ----------------------------------------------
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
	char result[10];
	int readResult2 = read(fds2[0], result, 3);
	//char buffer[30];
	//sprintf(buffer, "%d", result);
	//puts(buffer);
	
	cout << result << '\n';
	
	}
	//----------------------------------------- CHILD ------------------------------------------
	else if (pid == 0){
		
	char arr2[3];
	int readResultChild = read(fds[0], arr2, 3);
	
	if(readResultChild == -1){
		perror("Child: Error in read");
	}
	
	char* token = strtok(arr2, " ");

	int total = 0;
	
	while(token != NULL) {
		
		total += stoi(token);
		token = strtok(NULL, " "); 
		
	}
	
	//printf("%d \n", total);
	string s = to_string(total);
	char buff[sizeof(s)];
	for(int i = 0; i < sizeof(s); i++){
		buff[i] = s[i];
	}
	
	int sum = write(fds2[1], buff, 2);
	cout << buff << '\n';
	}

	else{
		perror("Fork failed in source code");
	}


	return 0;
}
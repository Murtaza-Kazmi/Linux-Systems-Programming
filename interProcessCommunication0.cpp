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

int main(){
	
	int fd = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	
	int pid = fork();
	
	if(pid > 0){
	
	int arr[3];
	
	cout << "Heyp1\n";
	int readResult = read(STDOUT_FILENO, arr, 3);
	
	if(readResult < 0){
		perror("Error in read");
	}
	
	
	
	if(fd < 0){
			perror("Error in open");
	}
	
	int writeResult = write(fd, arr, 3);

	//close(fd);
	
	if(writeResult < 0){
		perror("Error in read");
	}
	
	//sprintf("h", "%d", 1);
	cout << "Heyp2\n";
	
	}
	
	else if (pid == 0){
		
	cout << "Heyc1\n";
	cout << "Heyc1\n";
		
	char inputs[50];
	
	int count = read(fd, inputs, 50);
	

	
	for(int  i= 0; i < count-1; i++){
		if(inputs[i] != ' '){
		if(!isdigit(inputs[i])){
			//print error here
			exit(1);
		}
		}
		
	}
	
	char* token = strtok(inputs, " ");

	int total = 0;
	
	while(token != NULL) {
		
		total += stoi(token);
		token = strtok(NULL, " "); 
		
	}
	cout << "Heyc2\n";
	cout << total;
	//sprintf("Answer", "%d", total);
	
	}

	else{
		perror("Fork failed in source code");
	}





	return 0;
}
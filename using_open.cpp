#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

//for cout:
#include <iostream>

//for using strings
#include <string> 
using namespace std;
void copy(string source, string destination){
	
	char input[50];
	
	int source_fd = open(source, O_RDWR | O_CREAT, S_IRWXU);
	
	if(source_fd== -1){
		write(STDIN_FILENO, "Error in opening source file\n", sizeof("Error in opening source file\n"));
		exit(1);
	}
	
	int destination_fd = open(destination, O_RDWR | O_CREAT, S_IRWXU);
	
	if(destination_fd== -1){
		write(STDIN_FILENO, "Error in opening destination file\n", sizeof("Error in opening destination file\n"));
		exit(1);
	}
	
	
	int read_result = 1;
	int write_result;
	
	for(int i = 0; input[read_result-1] != '\0'; i++){
		
	read_result = read(source_fd, input, 30);
	
	if(read_result == -1){
		write(STDIN_FILENO, "Error in reading\n", sizeof("Error in reading\n"));
		exit(1);
	}
	
	write_result  = write(destination_fd, input, read_result);
	
	if(write_result == -1){
		write(STDIN_FILENO, "Error in writing\n", sizeof("Error in writing\n"));
		exit(1);
	}
	
	}
	
	write(1, "Successfully copied!\n", sizeof("Successfully copied!\n"));
	
}

int main() {
	//write(1, "Successfully copied!\n", sizeof("Successfully copied!\n"));
	copy("a.txt", "b.txt");
	
	return 0;
}


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

//bool is_fd_error(int fd){
//	return fd == -1;
//}



/*
	int fd  = open("b.txt", O_RDWR | O_CREAT, S_IRWXU);
	
	if(fd== -1){
		write(STDIN_FILENO, "Error in opening\n", sizeof("Error in opening\n"));
		exit(1);
	}
	
	//mode_t mode = S_IRWXG;
	int write_result  = write(fd, "abcde", sizeof("abcde")-1);
	//string s;
	//sscanf("Enter input "   ,"%s", &s);
	if(write_result == -1){
		write(STDIN_FILENO, "Error in writing\n", sizeof("Error in writing\n"));
		exit(1);
	}
	*/

	/*
	char input[50];
	
	int f = open("file", O_RDONLY);
	
	if(f == -1){
		write(STDIN_FILENO, "Error in opening\n", sizeof("Error in opening\n"));
		exit(1);
	}
	
	int read_result = 1;
	int write_result;
	
	for(int i = 0; input[read_result-1] != '\0'; i++){
	read_result = read(f, input, 30);
	
	//errno == EBADF
	if(read_result == -1){
		write(STDIN_FILENO, "Error in reading\n", sizeof("Error in reading\n"));
		exit(1);
	}
	
	int write_result  = write(STDIN_FILENO, input, read_result);
	write(STDIN_FILENO, "\n", 1);
	
	if(write_result == -1){
		write(STDIN_FILENO, "Error in writing\n", sizeof("Error in writing\n"));
		exit(1);
	}
	
	}
	
	char input2[50];
	//////////////////////////////////////////////////// OPENING FILE
	int f2 = open("file", O_RDWR);
	
	if(f2== -1){
		write(STDIN_FILENO, "Error in opening\n", sizeof("Error in opening\n"));
		exit(1);
	}
	//////////////////////////////////////////////////// READING FILE
	read_result = read(f2, input2, 30);
	
	if(read_result == -1){
		write(STDIN_FILENO, "Error in reading\n", sizeof("Error in reading\n"));
		exit(1);
	}
	//////////////////////////////////////////////////// WRITING FILE
	write_result  = write(f2, "y", 2);
	
	if(write_result == -1){
		write(STDIN_FILENO, "Error in writing\n", sizeof("Error in writing\n"));
		exit(1);
	}
	
	char enter = 'y';
	int write2 = write(f2, &enter, 1);
	
	//////////////////////////////////////////////////// READING FILE
	read_result = read(f2, input2, 30);
	
	write_result  = write(STDIN_FILENO, input, read_result);
	
	
	////////////////////////////////////////////////////////////////////////////////////
	
	*/
	
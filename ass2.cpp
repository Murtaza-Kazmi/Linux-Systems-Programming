 #include <unistd.h>
 #include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <ctime>

//for cout:
#include <iostream>

//for using strings
#include <string> 
using namespace std;

 int fsync(int fd);

 int fdatasync(int fd);
 
void copyNormally(char* source, char* destination){
	
	char input[50];
	/*
	char s[10];
	char d[10];
	for(int i =0; source[i-1] != '\0'; i++){
		s[i] == source[i];
	}
	
	for(int i =0; destination[i-1] != '\0'; i++){
		d[i] == destination[i];
	}
	cout << s;
	cout << d;
	*/
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
// while EOF character is read
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

//calls fsync after after 1000 bytes
void copyFsync(char* source, char* destination){
	
	char input[1000];
	
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
		//if(i <= 5)
		//cout << input[i];
		
	read_result = read(source_fd, input, 1000);
	//cout << read_result << '\n';
	
	if(read_result == -1){
		write(STDIN_FILENO, "Error in reading\n", sizeof("Error in reading\n"));
		exit(1);
	}
	
	write_result  = write(destination_fd, input, read_result);
	
	if(write_result == -1){
		write(STDIN_FILENO, "Error in writing\n", sizeof("Error in writing\n"));
		exit(1);
	}
	
	fsync(destination_fd);
	
	}
	
	write(1, "Successfully copied!\n", sizeof("Successfully copied!\n"));
	
}

//calls fdatasync after after 1000 bytes
void copyFDataSync(char* source, char* destination){
	
	char input[1000];
	
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
		//if(i <= 5)
		//cout << input[i];
		
	read_result = read(source_fd, input, 1000);
	//cout << read_result << '\n';
	
	if(read_result == -1){
		write(STDIN_FILENO, "Error in reading\n", sizeof("Error in reading\n"));
		exit(1);
	}
	
	write_result  = write(destination_fd, input, read_result);
	
	if(write_result == -1){
		write(STDIN_FILENO, "Error in writing\n", sizeof("Error in writing\n"));
		exit(1);
	}
	
	fdatasync(destination_fd);
	
	}
	
	write(1, "Successfully copied!\n", sizeof("Successfully copied!\n"));
	
}

//copies with osync flag
void copyOSync(char* source, char* destination){
	
	char input[1000];
	
	int source_fd = open(source, O_RDWR | O_CREAT | O_SYNC, S_IRWXU);
	
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
		//if(i <= 5)
		//cout << input[i];
		
	read_result = read(source_fd, input, 1000);
	//cout << read_result << '\n';
	
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

//copies byte by byte and calls fsync after writing each byte
void copyFSync1Byte(char* source, char* destination){
	
	char input[1];
	
	int source_fd = open(source, O_RDWR | O_CREAT | O_SYNC, S_IRWXU);
	
	if(source_fd== -1){
		write(STDIN_FILENO, "Error in opening source file\n", sizeof("Error in opening source file\n"));
		exit(1);
	}
	
	int destination_fd = open(destination, O_RDWR | O_CREAT, S_IRWXU);
	
	if(destination_fd== -1){
		write(STDIN_FILENO, "Error in opening destination file\n", sizeof("Error in opening destination file\n"));
		exit(1);
	}
	
	int read_result;
	int write_result;
	int bytes = 11624426;
	for(int i = 0; i < bytes; i++){
		//if(i <= 5)
		//cout << input[i];
		
	read_result = read(source_fd, input, 1);
	//cout << input << '\n';
	
	if(read_result == -1){
		write(STDIN_FILENO, "Error in reading\n", sizeof("Error in reading\n"));
		exit(1);
	}
	
	write_result  = write(destination_fd, input, read_result);
	
	if(write_result == -1){
		write(STDIN_FILENO, "Error in writing\n", sizeof("Error in writing\n"));
		exit(1);
	}
	
	fsync(destination_fd);
	
	}
	
	write(1, "Successfully copied!\n", sizeof("Successfully copied!\n"));
	
}

int main() {
	
	time_t startTime;
	time_t endTime;

	startTime = time(NULL);
		
	//copyNormally("11MB.txt", "copyOf11MB.txt");
	//copyFsync("11MB.txt", "copyOf11MB.txt");
	//copyFDataSync("11MB.txt", "copyOf11MB.txt");
	//copyOSync("11MB.txt", "copyOf11MB.txt");
	copyFSync1Byte("11MB.txt", "copyOf11MB.txt");
	
	endTime = time(NULL);
	time_t consumedTime = endTime-startTime;
	cout << "Start time: " << startTime << '\n';
	cout  << "End time: "<< endTime << '\n';
	cout  << "Consumed time: "<< consumedTime << '\n';
	
	return 0;
}


/*
	
*/
// read, write
#include <unistd.h>

//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// printf
#include <stdio.h>

// exit
#include <stdlib.h>


#include <cerrno>


// parent mein fork

// file deleted what happens

// read permission only, do write and check error

// write permission only, do read and check error
#include <iostream>
using namespace std;

int main(){
	
	
	//read permission only and trying write
	char name[5] = "../f";
	int o = open(name, O_RDWR |  O_CREAT);
	
	if(o == -1){
		perror("error in open");
		exit(1);
	}
	
	int w = write(o, "ABCD", 4);
	
	if(w == -1){
		printf("Error in write");
		if(errno == EPERM) printf("eperm");
		cout << errno ;
		exit(1);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
	
}

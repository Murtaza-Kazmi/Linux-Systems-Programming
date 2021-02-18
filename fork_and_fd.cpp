//for open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//for write, fork
#include <unistd.h>

//for fork only
#include <sys/types.h>

//for cout
#include <iostream>

//cout
using namespace std;

bool open_error(int fd){
	if(fd == -1){
		write(STDIN_FILENO, "Error in opening source file\n", sizeof("Error in opening source file\n"));
		exit(1);
	}
	return true;
	
}

int main() {
	
	char input[50];
	
	//open fd1
	int fd1 =  open("c.txt", O_RDWR | O_CREAT, S_IRWXU);
	bool check_open  = open_error(fd1);
	
	//fork
	int pid = fork();
	
	//write fd1
	write(fd1, "ABC", sizeof("ABC")-1);
	
	//open fd2
	int fd2 =  open("c.txt", O_RDWR | O_APPEND, S_IRWXU);
	check_open  = open_error(fd2);
	
	
	//write fd2
	write(fd2, "XYZ", sizeof("XYZ")-1);
	
	
	//child section
	if(pid == 0){
		int fd3 = open("c.txt", O_RDWR | O_CREAT, S_IRWXU);
		write(fd3, "123", sizeof("123")-1);
		
	}
	else if(pid > 0){
		int fd3  = open("c.txt", O_RDWR | O_CREAT,  S_IRWXU);
		write(fd3, "LMS", sizeof("LMN")-1);
	}
	
	else {
		cout << "error\n";
	}
	
	return 0;
}

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
	
	//open fd1
	int fd1 =  open("d.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	bool check_open  = open_error(fd1);

	//write fd1
	write(fd1, "123456", sizeof("123456"));
	
	//open fd2
	int fd2 =  open("d.txt", O_RDWR | O_TRUNC, S_IRWXU);
	check_open  = open_error(fd2);
	
	//write fd2
	write(fd2, "A", sizeof("A"));
	write(fd2, "910", sizeof("910"));
	
	
	return 0;
}

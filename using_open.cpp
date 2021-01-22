#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

/*
bool noZeroChar(char arr[]){
	
	for(int i = 0; i < sizeof
	
	
	
}
*/


int main() {

	char input[50];
	//while(noZeroChar(input)){
	int f = open("file", O_RDONLY);
	
	if(f == -1){
		write(STDIN_FILENO, "Error in opening\n", sizeof("Error in opening\n"));
		exit(1);
	}
	
	int read_result = read(f, input, 30);
	//errno == EBADF || 
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
	
	
	//}








	return 0;
}
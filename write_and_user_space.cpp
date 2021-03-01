#include <iostream>
#include <cstring>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

int main(){

	char arr[4];
	arr[0] = 'a';
	arr[1] = 'b';
	
	int destination_fd = open("e.txt", O_RDWR | O_CREAT, S_IRWXU);
	
	int write_result  = write(destination_fd, arr, 2);
	
	//for error
	char *buff[500];
	strcpy(buff[0], "ABC");	//gives segmentation fault
	
	return 0;

}
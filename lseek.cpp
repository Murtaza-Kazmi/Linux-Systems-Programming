//for lseek
#include <sys/types.h>
#include <unistd.h>

//for open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//for printf
#include <stdio.h> 




int main(){

	char buffer[7]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
	
	char b;
	
	int fd = open("a.txt",  O_RDWR | O_CREAT, S_IRWXU);
	
	if(fd < 0){
		
		perror("Error in open");
		//exit(1);
	}

	int writeResult = write(fd, buffer, sizeof(buffer));
	
	printf("%ld\n",sizeof(buffer));
	if(writeResult < 0){
		perror("Error in write");
		//exit(1);
	}
	
	int r = lseek(fd, 3, SEEK_CUR);
	
	int output = read(fd, &b, 1);
	
	printf("%c\n",b);



	return 0;

	
}
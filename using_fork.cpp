//for write, fork
#include <unistd.h>

//for fork only
#include <sys/types.h>

//for cout
#include <iostream>

//cout
using namespace std;

int main() {

	int pid = fork();
	write(STDOUT_FILENO, "Hi 1\n", sizeof("Hi 1\n"));
	//cout << "Hi\n";
	
	if(pid > 0){
		//cout << "Hi\n";
		write(STDOUT_FILENO, "Hi. Parent here.\n", sizeof("Hi. Parent here.\n"));
		write(STDOUT_FILENO, "I am in parent\n", sizeof("I am in parent\n"));
	
	}
	
	else if(pid == 0){
		cout << "Hi. Child here\n";
		write(STDOUT_FILENO, "I am in child\n", sizeof("I am in child\n"));
	}
	
	else {
		perror("Fork fail\n");
	}
	
	write(STDOUT_FILENO, "Hi 2\n", sizeof("Hi 2\n"));
	//cout << "Hi\n";
	
	getchar();
	//^runs later since it is an I/O call - so the process goes into blocked queue. When enter is pressed, parent  process should get
	// released followed by child process.
	
	
	write(STDOUT_FILENO, "Hi 3\n", sizeof("Hi 3\n"));
	
	//do ps -au
}

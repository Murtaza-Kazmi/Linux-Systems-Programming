#include <sys/types.h>
#include <signal.h>

//for waitpid
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>

#include <iostream>

#include <string>
using namespace std;

int main(int argc, char* argv[]){
	

	// //waitpid(pid_t pid, int *wstatus, int options);

	// int f  = fork();

	// if(f > 0){
	// 	int pid = waitpid(f, , WNOHANG);
	// }
	// else if(f == 0){
	// 	exit(1);
	// }
	// else{
	// 	perror("Error in fork");
	// }

	



	// cout << argc << '\n';
	
	// if(argc != 3)	cout << "Invalid number of arguments\n";
	
	// else{
	
	// for(int i = 0; i < argc; i++) cout << argv[i] << '\n';
	
	// cout << "Done printing args\n\n";
	// string h = argv[1];

	// if(h == "kill"){

	// int pid = atoi(argv[2]);
	
	// cout << "Killing process with id: " << pid << '\n';
	
	// kill(pid, SIGTERM);
	// }
	// else{
	// 	cout << "Error" <<'\n';
	// }

	// }




	return 0;
}
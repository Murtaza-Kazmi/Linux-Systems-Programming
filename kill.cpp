#include <sys/types.h>
#include <signal.h>

#include <iostream>

#include <string>
using namespace std;

int main(int argc, char* argv[]){
	
	cout << argc << '\n';
	
	if(argc != 3)	cout << "Invalid number of arguments\n";
		
	
	for(int i = 0; i < argc; i++) cout << argv[i] << '\n';
	
	cout << "Done printing args\n\n";
	string h = argv[1];

	if(h == "kill"){

	int pid = atoi(argv[2]);
	
	cout << pid << '\n';
	
	kill(pid, SIGTERM);
	}
	else{
		cout << "Error" <<'\n';
	}


	return 0;
}
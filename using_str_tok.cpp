#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
/*
Imports specs
	stdio for printf
	unistd for read
	string for strtok
	iostream for stoi
*/

//for cout:
using namespace std;
int main() {
	
	char inputs[50];
	
	int count = read(0, inputs, 50);
	
	if (errno == EBADF){
		cout << "Error in read\n";
		exit(1);
	}
	
	for(int  i= 0; i < count-1; i++){
		if(inputs[i] != ' '){
		if(!isdigit(inputs[i])){
			cout << "Invalid argument error\n";
			exit(1);
		}
		}
		
	}
	
	char* token = strtok(inputs, " ");

	int total = 0;
	
	while(token != NULL) {
		
		total += stoi(token);
		token = strtok(NULL, " "); 
		
	}
	
	printf("%d \n", total);
	
	return 0;
}
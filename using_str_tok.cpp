#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
int main() {
	
	char inputs[50];
	
	int count = read(0, inputs, 50);
	
	//defining pointer, since strtok returns one
	char* token = strtok(inputs, " ");


	int total = 0;

	while(token != NULL) {
		
		total += stoi(token);
		token = strtok(NULL, " "); 
		
	}
	
	printf("%d \n", total);
	
	return 0;
}
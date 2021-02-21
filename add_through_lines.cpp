#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <cmath>

/*
Imports specs
	iostream for errno, isdigit, ebadf
	stdio for printf
	unistd for read
	cmath for pow
*/

int main() {
	
	/*
	The list in this assignment will be terminated with a ; meaning a single list 
	can span over multiple lines OR a single line can have multiple lists. 
	The input naturally can still be taken with an enter. ; will come after space.	
	*/
	
	// 2; is invalid
	
	int total = 0;
	
	while(true){
		
	char inputs[50];
	int count = read(0, inputs, 50);
	int num = 0; //current num 
	
	if (errno == EBADF){
		printf("Error in read\n");
		exit(1);
	}
	
	for(int  i= 0; i < count-1; i++){

		if(inputs[i] == ' ') continue; 
		
		else if(inputs[i] == ';'){
			if(i != 0 && inputs[i-1] != ' '){
				printf("Invalid argument error\n");
				exit(1);
			}
			printf("%d \n", total);
			total = 0;
		}
		
		else {
		if(!isdigit(inputs[i])){
			printf("Invalid argument error\n");
			exit(1);
		}
		
		if(i == 0){
			num = inputs[i] - '0';
			total += num;
			continue;
		}
		
		int k = i;
		int positionFromRight = 0;
		//add the current number as multiples of 10 since reading is done char by char  
		while(inputs[k] != ' ' && k != -1){
			num = inputs[k] - '0';			
			num = num * pow(10,positionFromRight);
			total += num;
			k--;
			positionFromRight++;
		}
		//now we delete the previously read number because we read it assuming there is no digit of that number left
		positionFromRight = 0;
		k = i - 1;
		while(inputs[k] != ' ' && k != -1){

			num = inputs[k] - '0';
			num = num * pow(10,positionFromRight);
			total -= num;
			k--;
			positionFromRight++;
		}
		}
	}
	//endOfLoop
	}
	return 0;
}
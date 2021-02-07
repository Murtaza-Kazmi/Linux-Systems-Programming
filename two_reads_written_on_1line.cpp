#include <unistd.h>
#include <stdio.h>

int main() {
	char input1[31];
	char input2[31];
	int r1 = read(0,  input1, 30 );
	int r2 = read(0, input2, 30);
	
	//printf("%s + %s", 	input1, input2);
	
	// since r1 and r2 both have one extra char 
	r1 -= 1;
	r2 -= 1;
	int total = r1 + r2;
	
	char result[total];

	//using single write
	for(int i = 0; i < total; i++){
		if(i < r1) result[i] = input1[i];
		else {
			result[i] = input2[i-r1];
		}
		
	}
	write(1, result, total);
	
	//using two writes
	write(1, "\n", 1);
	write(1, input1, r1);
	write(1, input2, r2);
	
	return 0;

}
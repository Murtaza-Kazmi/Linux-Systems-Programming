#include <iostream>
#include <cstring>

using namespace std;

int main(){

	//array of char pointers
	//buff[0] = 8 bytes
	char *buff[500];
	cout << sizeof(buff) <<"\n";
	
	//array of chars
	char buff2[500];
	cout << sizeof(*buff2) <<"\n";
	
	cout << sizeof(buff2) <<"\n";
	
	//strcopy(buff[0], "ABC");
	//buff[0] is pointer
	//"ABC" is a string = sequence of chars. Also a pointer
	//it accepts both parameters as pointers
	
	//but if buff2 is used, it will give error
	
	
	strcpy(buff2[0], "ABC"); //compilation error
	
	strcpy(buff[0], "ABC");	//gives segmentation fault
	
	/*
	
	int b;
	b -> 20 (garbage value)
	*b -> 650
	&b -> 500
	
	
	*/
	
	return 0;

}
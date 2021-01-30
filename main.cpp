#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string>

//for sscanf, sprintf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

// includes dumps code. located at usr/include/

int main()
{
	if(true){
    // cout << STDOUT_FILENO << "\n";
    int output = write(30,"Hello, World!\n", 14);
	
	//string x =  " " + errno;
	//perror(x);
	
	cout << errno << "\n";
	//printf can be used too 
	
	
	
	if(output == -1){
	
    if(errno == EBADF){
       // write(STDOUT_FILENO,"Ebadf agaya!\n", 50);
    }
	 
	}
    char inp [20];

    read(STDIN_FILENO, inp, 20);
	
	if (errno == EBADF){
//        write(STDOUT_FILENO,"Ebadf agaya!\n", 50);
    }
	else {
	cout << inp ;
	}
	
	}
	int a, b,c;
	

   sscanf("Enter input "   ,"%d %d", &a, &b);
   //sscanf("Enter input "   ,"%d", &b);
   int max  = 2147483647;
   //read(STDIN_FILENO, &a, sizeof(max));
   //read(STDIN_FILENO, &b, sizeof(max));
   

	c = a +b;
	write(c,&c, sizeof(c));
	// returned garbage value
	
   printf("%d %d", a, b);
   
   //write(STDOUT_FILENO,&a, sizeof(a));
   //write(STDOUT_FILENO,&b, sizeof(b));
   
   //scanf limitation?
   //we need to tell how many numbers we are gonna pick up 
   //can use string tok
   
   
    return 0;
}

//aethetics101
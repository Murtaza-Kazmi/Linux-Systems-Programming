
/* Problem Statement -------------------------------------------------------------------------------------
run app_name (give success/error message)
exit (exits entire app)
add 1 2 
sub 2 3 4
div 2 3 4
mul 3 4 5
*/

// preprocessor directives -------------------------------------------------------------------------------

//to use string:
#include <string>
using namespace std;

//to compare char*s
#include <cstring>

// for system calls: pipe
#include <unistd.h>

// for strtok
#include <string.h>

// main --------------------------------------------------------------------------------------------------

int main(){
    
    //initializing two pipes for smoking input output -------------------------------
    int fdClientToServer[2];
	int fdServerToClient[2];
	
	int pipeResult1 = pipe(fdClientToServer);
    if(pipeResult1 < 0){
        perror("Error in first pipe initialization.");
        exit(1);
    }

	int pipeResult2 = pipe(fdServerToClient);
    if(pipeResult2 < 0){
        perror("Error in second pipe initialization.");
        exit(1);
    }
    // initialized pipes -------------------------------------------------------------
	
	

    int pid = fork(); // kun faya kun -----------------------------------------------------------------------------------

    //reversed roles
    if(pid == 0){ // child (server) --------------------------------------------------------------------------------------
        // char arr[sizeof("Connection established.")] = "Connection established.";
        // int writeResult = write(fdServerToClient[1], arr, sizeof(arr)-1);
	    // if(writeResult < 0){
		// perror("Server: Error in write");
	    // }

        
    }
    else if(pid > 0){ // parent (client) ---------------------------------------------------------------------------------
        
        //buffer used for sprintf 	
        char buff1[100];

        //buffer used for read 	
        char buff0[100];

        int argc;
        char* argv[100];
        int noOfBytesRead;

        // char arr2[100];
        // int readResultChild = read(fdServerToClient[0], arr2, sizeof(arr2)-1);
        
        // if(readResultChild == -1){
        //     perror("Client: Error in read");
        // }
        
        // sprintf(buff1, "%s", arr2);
        // puts(buff1);

        while(true){

        
        noOfBytesRead = read(0, buff0, 100);

        if(noOfBytesRead == -1){
            perror(("Error in read."));
        }

        //adding input delimited by single space to argv array
        char* token = strtok(buff0, " ");
        int ind = 0;
        while(token != NULL) {
            
            argv[ind] = token;
            ind += 1;
            token = strtok(NULL, " "); 
            
        }
        //added input delimited by single space to argv array

        // arg count:
        argc = ind;

        if(argc < 2){
            sprintf(buff1, "Invalid number of arguments. Please enter again.");
            puts(buff1);
            continue;
        }

        //prints input token line by line
        // for(int i = 0; i < argc; i++){
        //     //s means char*
        //     sprintf(buff1, "%s", argv[i]);
        //     puts(buff1);
        // }

        //char* is pointer to a sequence of chars in memory (ends with '\0')
        char* requirement = argv[0];
        char* requirement2 = argv[1];

        //sprintf helps write formatted output
        sprintf(buff1, "Number of arguments = %d", argc);
        puts(buff1);
        
        if(strcmp(requirement, "add") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);

            int total = 0;
            bool canAdd = true;
            char* current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                for(int j = 0; j < sizeof(*current); j++){
                    if(!isdigit(current[j])){
                        canAdd = false;
                        break;
                    }
                }
                if(canAdd){
                    total += atoi(argv[i]);
                }
                else{
                    break;
                }
            }
            // for loop ended ----------------------------

            if(canAdd){
                sprintf(buff1, "The total is: %d.", total);
                puts(buff1);
            }
            else{
                sprintf(buff1, "Invalid input. Please enter numbers only.");
                puts(buff1);
                continue;
            }
        }
        else if(strcmp(requirement, "sub") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);

            int total = 0;
            bool canAdd = true;
            char* current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                
                for(int j = 0; j < sizeof(*current); j++){
                    if(!isdigit(current[j])){
                        canAdd = false;
                        break;
                    }
                }
                if(canAdd){
                    if(i == 1) total += atoi(argv[i]);
                    else total -= atoi(argv[i]);
                }
                else{
                    break;
                }
            }
            // for loop ended ----------------------------

            if(canAdd){
                sprintf(buff1, "The total is: %d.", total);
                puts(buff1);
            }
            else{
                sprintf(buff1, "Invalid input. Please enter numbers only.");
                puts(buff1);
                continue;
            }
        }
        else if(strcmp(requirement, "mul") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);

            int total = 1;
            bool canAdd = true;
            char* current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                for(int j = 0; j < sizeof(*current); j++){
                    if(!isdigit(current[j])){
                        canAdd = false;
                        break;
                    }
                    sprintf(buff1, "Here %d", current[j]);
                    puts(buff1);
                }
                if(canAdd){
                    total = total * atoi(argv[i]);
                }
                else{
                    break;
                }
            }
            // for loop ended ----------------------------

            if(canAdd){
                sprintf(buff1, "The total is: %d.", total);
                puts(buff1);
            }
            else{
                sprintf(buff1, "Invalid input. Please enter numbers only.");
                puts(buff1);
                continue;
            }
        }
        else if(strcmp(requirement, "div") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);

            float total = 1;
            bool canAdd = true;
            char* current;
            bool divisionByZero = false;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                for(int j = 0; j < sizeof(*current); j++){
                    if(!isdigit(current[j])){
                        canAdd = false;
                        break;
                    }
                }
                if(canAdd){
                    if(atoi(argv[i]) == 0) {
                        divisionByZero = true;    
                        break;
                    }
                    else{
                        if(i == 1) total = atoi(argv[i]);
                        else total = total/atoi(argv[i]);
                    }
                }
                else{
                    break;
                }
            }
            // for loop ended ----------------------------

            if(canAdd){
                sprintf(buff1, "The total is: %f", total);
                puts(buff1);
                continue;
            }
            if(divisionByZero){
                sprintf(buff1, "Invalid input. Division by zero not possible.");
                puts(buff1);
                continue;
            }
            sprintf(buff1, "Invalid input. Please enter numbers only.");
            puts(buff1);
            continue;
            
        }
        else if(strcmp(requirement, "run") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);
        }
        else if(strcmp(requirement, "exit") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);
        }
        else if(strcmp(requirement, "end") == 0){
                sprintf(buff1, "Program terminated.");
                puts(buff1);
                exit(1);
        }
        else{
            sprintf(buff1, "Invalid requirement. Please re-enter.");
            puts(buff1);
        }
     }
    }
    else{
        perror("fork() gave an error.");
        exit(1);
    }

    return 0;
}
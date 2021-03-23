
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

    
    if(pid == 0){ // child (server) --------------------------------------------------------------------------------------
        // char arr[sizeof("Connection established.")] = "Connection established.";
        // int writeResult = write(fdServerToClient[1], arr, sizeof(arr)-1);
	    // if(writeResult < 0){
		// perror("Server: Error in write");
	    // }

        while(true){

        int argc;
        char* argv[100];

        //buffer used for read 	
        char buff0[100];

        //buffer used for sprintf 	
        char buff1[100];

        //there could be garbage values in buff0
        for(int i = 0; i < 100; i++){
            buff0[i] = '\0';
        }

        int readResult = read(fdClientToServer[0],  buff0, sizeof(buff0)-1);

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

        
        // prints input token line by line
        // for(int i = 0; i < argc; i++){
        //     //s means char*
        //     sprintf(buff1, "%s", argv[i]);
        //     puts(buff1);
        // }


        //char* is pointer to a sequence of chars in memory (ends with '\0')
        char* requirement = argv[0];
        char* requirement2 = argv[1];


        if(argc < 2){
            sprintf(buff1, "Invalid number of arguments. Please enter again.");
        }
        else if(strcmp(requirement, "add") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);

            int total = 0;
            bool canAdd = true;
            //used to calculate length
            string current;
            
            
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];

                for(int j = 0; j < current.length()-1; j++){
                    if(!isdigit(argv[i][j])){
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
            }
            else{
                sprintf(buff1, "Invalid input. Please enter numbers only.");
            }
        }
        else if(strcmp(requirement, "sub") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);

            int total = 0;
            bool canAdd = true;
            string current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                
                for(int j = 0; j < current.length()-1; j++){
                    if(!isdigit(argv[i][j])){
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
            }
            else{
                sprintf(buff1, "Invalid input. Please enter numbers only.");
            }
        }
        else if(strcmp(requirement, "mul") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);

            int total = 1;
            bool canAdd = true;
            string current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                for(int j = 0; j < current.length()-1; j++){
                    if(!isdigit(argv[i][j])){
                        canAdd = false;
                        break;
                    }
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
            }
            else{
                sprintf(buff1, "Invalid input. Please enter numbers only.");
            }
        }
        else if(strcmp(requirement, "div") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);

            float total = 1;
            bool canAdd = true;
            string current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                for(int j = 0; j < current.length()-1; j++){
                    if(!isdigit(argv[i][j])){
                        canAdd = false;
                        break;
                    }
                }
                if(canAdd){
                    if(atoi(argv[i]) == 0) {
                        canAdd = false;    
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
                sprintf(buff1, "The total is: %f.", total);
            }
            else{
                sprintf(buff1, "Invalid input. Please enter numbers only.");
            }
        }
        else if(strcmp(requirement, "run") == 0){
            sprintf(buff1, "Requirement to run %s received.", argv[1]);
            puts(buff1);
            
            string current = argv[1];
            char name[current.length()-1];

            for(int i = 0; i < current.length(); i++){
                name[i] = argv[1][i];
            }

            int fdServerChildToServer[2];

            int pipeRes = pipe(fdServerChildToServer);

            if(pipeRes < 0){
                sprintf(buff1, "Server: error in initiating pipe on server for creating new process.");
            }

            else{
            int newPID = fork();

            if(newPID < 0){
                sprintf(buff1, "Server: error in fork before execution.");
            }
            else if(newPID == 0){ // child
                sprintf(buff1, "Success");
                int writeRes = write(fdServerChildToServer[1], buff1, sizeof(buff1)-1);
                // call exec, make it generic
                // sprintf(buff1, "/usr/bin/%s", name);
                // puts(buff1);
                // sprintf(buff1, "/usr");
                int execResult = execlp(name, name,  NULL);
                sprintf(buff1, "Error");
                writeRes = write(fdServerChildToServer[1], buff1, sizeof(buff1)-1);
                //end this process
                exit(1);
            }
            else{
            //parent - keep it running
                sprintf(buff1, "Parent");
                int writeRes = write(fdServerChildToServer[1], buff1, sizeof(buff1)-1);
                int readRes = read(fdServerChildToServer[0], buff1, sizeof(buff1)-1);
                readRes = read(fdServerChildToServer[0], buff1, sizeof(buff1)-1);
                readRes = read(fdServerChildToServer[0], buff1, sizeof(buff1)-1);
            }
            }
            
            
        }
        else if(strcmp(requirement, "exit") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);
        }
        else if(strcmp(requirement, "end") == 0){
                // sprintf(buff1, "Program terminated.");
                // puts(buff1);
                // exit(1);
        }
        else{
            sprintf(buff1, "Invalid requirement. Please re-enter.");
        }

        int responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);
        if(responseAttempt < 0){
            perror("Server: error in responding to client.");
        } 
        }

    }

    // parent (client) ---------------------------------------------------------------------------------

    else if(pid > 0){ 
        
        // char arr2[100];
        // int readResultChild = read(fdServerToClient[0], arr2, sizeof(arr2)-1);
        
        // if(readResultChild == -1){
        //     perror("Client: Error in read");
        // }
        
        // sprintf(buff1, "%s", arr2);
        // puts(buff1);

        while(true){

        //buffer used for read 	
        char buff0[100];

        //buffer used for sprintf 	
        char buff1[100];

        //reads until enter, so no garbage value
        int noOfBytesRead = read(0, buff0, 100);

        if(noOfBytesRead == -1){
            perror(("Error in read."));
        }
        
        // send input to server (sends the bytes inputted)
        // why does read not give error for last val?
        int writeResult = write(fdClientToServer[1], buff0, noOfBytesRead-1);
        if(writeResult < 0){
            perror("Error in writing from server to client.");
        }

        int readResponseResult = read(fdServerToClient[0], buff0, sizeof(buff0)-1);

        if(readResponseResult < 0){
            perror("Client: error in reading response sent by server.");
        }

        sprintf(buff1, "%s", buff0);
        puts(buff1);

        

        // while ends below
     }
    }
    else{
        perror("fork() gave an error.");
        exit(1);
    }

    return 0;
}
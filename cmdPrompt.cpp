
/* CLI input info -------------------------------------------------------------------------------------















*/

// preprocessor directives -------------------------------------------------------------------------------

//to use string, sprintf
 #include <string>

//to compare char*s, for strtok
#include <cstring>

// for system calls: pipe, exec
#include <unistd.h>


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

    int size = 10000;

    // initialized pipes -------------------------------------------------------------

    int pid = fork(); // kun faya kun -----------------------------------------------------------------------------------

    
    if(pid == 0){ // child (server) --------------------------------------------------------------------------------------

        while(true){
            
        int responseAttempt;
        int argc;
        char* argv[size];

        //buffer used for read 	
        char buff0[size];

        //buffer used for sprintf 	
        char buff1[size];

        //there could be garbage values in buff0
        for(int i = 0; i < size; i++){
            buff0[i] = '\0';
        }

        int readResult = read(fdClientToServer[0],  buff0, sizeof(buff0)-1);

        if(readResult < 0){
            sprintf(buff1, "Server: error in reading pipe client to server.");
            responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);
            continue;
        }

        //adds input delimited by single space to argv array
        char* token = strtok(buff0, " ");
        int ind = 0;
        while(token != NULL) {
            
            argv[ind] = token;
            ind += 1;
            token = strtok(NULL, " "); 
            
        }

        // arg count:
        argc = ind;

        if(argc == 1){
            if(strcmp(argv[0], "exit") == 0){
                sprintf(buff1, "Exit!");
                responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);
                exit(1);
            }
            else{
                sprintf(buff1, "Invalid requirements. Please re-enter.");
                responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);
                continue;
            }
        }
        // prints input token line by line
        // for(int i = 0; i < argc; i++){
        //     //s means char*
        //     sprintf(buff1, "%s", argv[i]);
        //     puts(buff1);
        // }


        //char* is pointer to a sequence of chars in memory (ends with '\0')
        char* requirement = argv[0];
        char* requirement2 = argv[1];


        if(strcmp(requirement, "add") == 0){

            int total = 0;
            bool canAdd = true;
            //used to calculate length
            char* current;
            
            
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];

                for(int j = 0; j < strlen(current); j++){
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
                sprintf(buff1, "Invalid input. Please enter valid numbers only.");
            }
        }
        else if(strcmp(requirement, "sub") == 0){

            int total = 0;
            bool canAdd = true;
            char* current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                
                for(int j = 0; j < strlen(current); j++){
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
                sprintf(buff1, "Invalid input. Please enter valid numbers only.");
            }
        }
        else if(strcmp(requirement, "mul") == 0){

            int total = 1;
            bool canAdd = true;
            char* current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                for(int j = 0; j < strlen(current); j++){
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
                sprintf(buff1, "Invalid input. Please enter valid numbers only.");
            }
        }
        else if(strcmp(requirement, "div") == 0){
            float total = 1;
            bool canAdd = true;
            char* current;
            // for loop begins ----------------------------
            for(int i = 1; i < argc; i++){
                canAdd = true;
                current = argv[i];
                for(int j = 0; j < strlen(current); j++){
                    if(!isdigit(argv[i][j])){
                        canAdd = false;
                        break;
                    }
                }
                //is an integer
                if(canAdd){
                        if(i == 1 && argv[i] == 0) total = 0;
                        else if(i == 1) total = atoi(argv[i]);
                        else if(total == 0.0){
                            total = 0;
                        }
                        else if(atoi(argv[i]) == 0){
                            canAdd = false;
                            break;
                        }
                        else total = total/atoi(argv[i]);
                    
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
                sprintf(buff1, "Invalid input. Please enter valid numbers only.");
            }
        }
        else if(strcmp(requirement, "run") == 0){
            
            char* current = argv[1];

            int l = strlen(current);

            char name[l+1];

            // sprintf(buff1, "res is %d and of string is %d", l, l2);
            // puts(buff1);

            for(int i = 0; i < l; i++){
                name[i] = argv[1][i];
            }
            name[l] = '\0';

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
                
                // call exec
                sprintf(buff1, "%s", name);
                // int execResult = execlp(name, name, NULL);
                int execResult = execlp(buff1, buff1, NULL);

                //if these lines run, execResult has returned -1 due to error
                sprintf(buff1, "Error");
                writeRes = write(fdServerChildToServer[1], buff1, sizeof(buff1)-1);

                //terminate this process
                exit(1);
            }
            else{
                //parent - keep it running
                int writeRes;
                int readRes;
                bool errorReceived = false;
                for(int i = 0; i < 10000; i++){
                    sprintf(buff1, "Parent");
                    writeRes = write(fdServerChildToServer[1], buff1, sizeof(buff1)-1);
                    readRes = read(fdServerChildToServer[0], buff0, sizeof(buff0)-1);
                    if(strcmp(buff0, "Error") == 0){
                        errorReceived = true;
                        break;
                    }
                }
                if(errorReceived){
                    sprintf(buff1, "Failure.");
                }
                else{
                    sprintf(buff1, "Success.");
                }
            }
            }
            
            
        }
        else if(strcmp(requirement, "exit") == 0){
            sprintf(buff1, "Exit!");
            responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);
            exit(1);
        }
        else{
            sprintf(buff1, "Invalid requirement. Please re-enter.");
        }

        responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);

        }

    }

    // parent (client) ---------------------------------------------------------------------------------

    else if(pid > 0){ 

        while(true){

        //buffer used for read 	
        char buff0[size];

        //buffer used for sprintf 	
        char buff1[size];

        //reads until enter, so no garbage value
        int noOfBytesRead = read(0, buff0, size-1);
        
        if(buff0[0] == '\n'){
            sprintf(buff1, "Invalid number of arguments. Please enter again.");
            puts(buff1);
            continue;
        }

        if(noOfBytesRead == -1){
            perror(("Error in read."));
        }
        
        // send input to server (sends the bytes inputted)
        int writeResult = write(fdClientToServer[1], buff0, noOfBytesRead-1);
        if(writeResult < 0){
            perror("Error in writing from server to client.");
        }

        int readResponseResult = read(fdServerToClient[0], buff0, sizeof(buff0)-1);

        if(readResponseResult < 0){
            perror("Client: error in reading response sent by server.");
        }

        sprintf(buff1, "%s", buff0);
        if(strcmp(buff1, "Exit!") == 0){
            sprintf(buff1, "Terminated.");
            puts(buff1);
            exit(1);
        }
        else{
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
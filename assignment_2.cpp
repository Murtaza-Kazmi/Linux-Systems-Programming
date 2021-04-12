
/* CLI input info -------------------------------------------------------------------------------------
run app_name (runs that application)
exit (exits entire app)
add 1 2 (adds all integers)
sub 2 3 4 (subtracts first integer from the rest)
div 2 3 4 (divides first integer from the rest)
mul 3 4 5 (multiplies all integers)

+ maintains a list of processes that you run. Additional commands:

 list (for active only) | list All

 Kill <pid> | Kill <name>

The lists keep track of elapsed time / execution time.

*/

// preprocessor directives -------------------------------------------------------------------------------

//for sprintf
 #include <string>

//for strcmp, strtok
#include <cstring>

// for system calls: pipe(), exec()
#include <unistd.h>

//for close-on-exec: O_CLOEXEC (read man pipe2)      
#include <fcntl.h>              

//for time
#include <ctime>

//for kill()
#define SIGTERM 15

//for waitpid
#include <sys/types.h>
#include <sys/wait.h>

// main --------------------------------------------------------------------------------------------------


int main(){


    class Process {       
        public:            
            char name[100];
            int pid;
            char status[10];
            time_t startTime;
    };

    int noOfProcessesAllowed = 100;
    Process processes[noOfProcessesAllowed];
    
    
    //initializing two pipes for smoking input output (client - server communication -------------------------------
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
        
        int processIndex = 0;

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
        char* requirement = argv[0];

        if(argc == 1){
            if(strcmp(requirement, "exit") == 0){
                sprintf(buff1, "Exit!");
                responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);
                exit(1);
            }
            else if(strcmp(requirement, "list") == 0){
                
                if(processIndex == 0){
                    sprintf(buff1, "Please initiate a process first.");
                }
                else{
                    time_t curTime = time(NULL);
                    sprintf(buff1, " ");

                    bool flag = false;

                    for(int i = 0; i < processIndex; i++){
                        time_t elapsedTime = curTime - processes[i].startTime;
                        if(strcmp(processes[i].status, "active") == 0){
                            flag = true;
                            sprintf(buff1, "%s\nIndex: %d              Name: %s             pID: %d          Start Time: %time_t          Elapsed Time: %time_t             Status:%s", buff1, i, processes[i].name, processes[i].pid, processes[i].startTime, elapsedTime, processes[i].status);
                        }
                    }
                    sprintf(buff1, "\n%s\nNote: me_t = seconds.", buff1);
                    if(!flag){
                        sprintf(buff1, "No active process.");
                    }
                }
            
        }
            else{
                sprintf(buff1, "Invalid requirements. Please re-enter.");
            }

            responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);
            continue;
        }
       
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
        else if(strcmp(requirement, "run") == 0){ // -------------------------------------------------------------- RUN -------------------------------------------------------------------------------------------
            
            char* current = argv[1];

            int l = strlen(current);

            char name[l+1];

            for(int i = 0; i < l; i++){
                name[i] = argv[1][i];
            }
            name[l] = '\0';

            int fdServerChildToServer[2];

            int pipeRes = pipe2(fdServerChildToServer, O_CLOEXEC);
            
            if(pipeRes < 0){
                sprintf(buff1, "Server: error in initiating pipe.");
            }

            else{
                
                int newPID = fork();

                if(newPID < 0){
                    sprintf(buff1, "Server: error in fork before execution.");
                }
                else if(newPID == 0){ // child
                                       
                    // call exec

                    sprintf(buff1, "%s", name);
                    int execResult = execlp(buff1, buff1, "-s", NULL);

                    write(fdServerChildToServer[1], "failure", 10);

                    //terminate this process
                    exit(1);
                }
                else{//parent - keep it running
                    
                    close(fdServerChildToServer[1]);
                    int res = read(fdServerChildToServer[0],  buff0, 10);
                    // sprintf(buff1, "%d", res);
                    // puts(buff1);
                    if(res == 0){//success
                         for(int i = 0; i < strlen(name); i++){
                            processes[processIndex].name[i] = name[i];
                        }
                        processes[processIndex].name[strlen(name)] = '\0';
                        processes[processIndex].startTime = time(NULL);
                        processes[processIndex].pid = newPID;
                        char temp[9] = "active"; //9 so that inactive is assignable
                        for(int i = 0; i < strlen("active"); i++){
                            processes[processIndex].status[i] = temp[i];
                        }
                        processes[processIndex].status[strlen("active")] = '\0';
                     
                        processIndex += 1;
                        sprintf(buff1, "Success.");
                    }
                    else{//exec has failed
                        sprintf(buff1, "exec() failed.");
                    }
            }
            }
            
         //run ends   
        }

        else if((strcmp(requirement, "list") == 0) && (strcmp(requirement2, "all") == 0)){
            if(processIndex == 0){
                sprintf(buff1, "Please initiate a process first.");
            }
            else{
            time_t curTime = time(NULL);
            sprintf(buff1, " ");
            for(int i = 0; i < processIndex; i++){
                time_t elapsedTime = curTime - processes[i].startTime;
                sprintf(buff1, "%s\nIndex: %d              Name: %s             pID: %d          Start Time: %time_t          Elapsed Time: %time_t             Status:%s", buff1, i, processes[i].name, processes[i].pid, processes[i].startTime, elapsedTime, processes[i].status);
            }
            sprintf(buff1, "\n%s\nNote: me_t = seconds.", buff1);
            }
        }

        else if(strcmp(requirement, "kill") == 0){// -------------------------------------------------------------- KILL -------------------------------------------------------------------------------------------
            
            bool isID = true;
            bool isName = true;
            
            for(int i = 0; i < strlen(requirement2); i++){
                if(!isdigit(requirement2[i])){
                    isID = false;
                }
                if(isdigit(requirement2[i])){
                    isName = false;
                }
            }
            if(!isName && !isID){
                sprintf(buff1, "Invalid id and/or name.");
            }
            else{
                bool success = true;
                bool inList = false;
                bool flag = true;

                if(isName){
                    for(int i = 0; i < processIndex; i++){
                        if(strcmp(processes[i].name, requirement2) == 0){
                            inList = true;
                            int res = kill(processes[i].pid, SIGTERM);
                            if (waitpid(processes[i].pid, NULL, WCONTINUED) < 0) {
                                sprintf(buff1, "Failed to collect child process");
                                flag = false;
                                break;
                            }                
                            if(res == 0){//mark inactive
                                char temp[9] = "inactive";
                                for(int j = 0; j < strlen("inactive"); j++){
                                    processes[i].status[j] = temp[j];
                                }
                                processes[i].status[strlen("inactive")] = '\0';
                                }
                            else{
                                sprintf(buff1, "Error in kill");
                                success = false;
                            }
                        }
                    }
                }
                else{
                    for(int i = 0; i < processIndex; i++){
                        if(processes[i].pid == atoi(requirement2)){
                            inList = true;
                            int res = kill(processes[i].pid, SIGTERM);
                            if(res == 0){ //mark inactive
                                char temp[9] = "inactive";
                                for(int j = 0; j < strlen("inactive"); j++){
                                    processes[i].status[j] = temp[j];
                                }
                                processes[i].status[strlen("inactive")] = '\0';
                                }
                            else{
                                sprintf(buff1, "Error in kill");
                                success = false;
                            }
                        }
                    }

                }
                if(success && inList){
                    sprintf(buff1, "Done killing.");
                }
                else{
                    if(flag){
                    sprintf(buff1, "Invalid id and/or name.");
                    }
                }
            }
            
        }
       
        else{
            sprintf(buff1, "Invalid requirement. Please re-enter.");
        }

        responseAttempt = write(fdServerToClient[1], buff1, sizeof(buff1)-1);
        
        //while ends
        }

    }

    // parent (client) ---------------------------------------------------------------------------------

    else if(pid > 0){ 

        while(true){

        //buffer used for read 	
        char buff0[size];

        //buffer used for sprintf 	
        char buff1[size];

        for(int i = 0; i < size; i++){
            buff0[i] = '\n';
            buff1[i] = '\n';
        }

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
        
        //while ends
     }
    }
    else{
        perror("fork() gave an error.");
        exit(1);
    }

    return 0;
}
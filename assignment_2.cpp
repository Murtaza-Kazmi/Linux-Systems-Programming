
/* Problem Statement -------------------------------------------------------------------------------------
run app_name (give success/error message)
exit app_name
add 1 2 
sub 2 3 4
*/

// preprocessor directives -------------------------------------------------------------------------------

//to use string:
#include <string>
using namespace std;

//to compare char*s
#include <cstring>

// for system calls
#include <unistd.h>

// for strtok
#include <string.h>

// main --------------------------------------------------------------------------------------------------

int main(){
	
	//buffer used for sprintf 	
    char buff1[100];

    //buffer used for read 	
    char buff0[100];

    int argc;
    char* argv[100];
    int noOfBytesRead;

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
        int argc = ind;

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

        sprintf(buff1, "Number of arguments = %d", argc);
        puts(buff1);

        //sprintf helps write formatted output
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
                for(int j = 0; j < sizeof(*current)-1; j++){
                    if(!isdigit(current[j])){
                        sprintf(buff1, "Here %c", current[j]);
                        puts(buff1);
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
                for(int j = 0; j < sizeof(*current)-1; j++){
                    if(!isdigit(current[j])){
                        sprintf(buff1, "Here %c", current[j]);
                        puts(buff1);
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
        else if(strcmp(requirement, "run") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);
        }
        else if(strcmp(requirement, "exit") == 0){
            sprintf(buff1, "Requirement to %s received.", requirement);
            puts(buff1);
        }
        else if(strcmp(requirement, "end") == 0){
            sprintf(buff1, "Exiting program.");
            puts(buff1);
            exit(1);
        }
        else{
            sprintf(buff1, "Invalid requirement. Please re-enter.");
            puts(buff1);
        }
     }

    return 0;
}
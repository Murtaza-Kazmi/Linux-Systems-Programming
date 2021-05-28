#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

void *print_message_function( void *ptr );

static pthread_mutex_t mutexed = PTHREAD_MUTEX_INITIALIZER;

class Process {       
        public:            
            char name[100];
            int pid;
            char status[10];
};

int main(){



    pthread_t thread3;
    const char *message3 = "Thread 3";
    pthread_t thread4;
    const char *message4 = "Thread 4";


    //creating detached thread
    pthread_attr_t attr;
    int inited = pthread_attr_init(&attr);
    if(inited){
        fprintf(stderr,"Error here: %d\n",inited);
    }

    int s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    if(s){
        fprintf(stderr,"Error here: %d\n",s);
    }

    pthread_t thread1, thread2;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    int  iret1, iret2, iret3, iret4;

/* Create independent threads each of which will execute function */

    iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);

    if(iret1){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);

    if(iret2){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        exit(EXIT_FAILURE);
    }

    
    iret3 = pthread_create( &thread3, &attr, print_message_function, (void*) message3);

    if(iret3){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3);
        exit(EXIT_FAILURE);
    }

    iret4 = pthread_create( &thread4, &attr, print_message_function, (void*) message4);
    
    if(iret4){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret4);
        exit(EXIT_FAILURE);
    }

    int det = pthread_detach(thread4);

    if(det){
         printf("Could not detach thread 4: %d\n", det);
         printf("Err: %d\n", errno);
         if(errno == EINVAL){
         printf("yes");
    }   
    }
    

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    Process *r;
    
    int attempt = pthread_join( thread1, (void **)  &r);
    if(attempt){
        printf("Could not join thread 1: %d\n", attempt);
    }
    int val = (*r).pid;
    printf("Got: %d\n",val);


    attempt = pthread_join( thread2, NULL);
    if(attempt){
        printf("Could not join thread 2: %d\n", attempt);
    }


    attempt = pthread_join( thread3, NULL);
    if(attempt){
        printf("Could not join thread 3: %d\n", attempt);
    }
    attempt = pthread_join( thread4, NULL);
    if(attempt && attempt == EINVAL){
        printf("Could not join thread 4: %d\n", attempt);
    }
    return 0;
}

void *print_message_function( void *ptr ){
    pthread_mutex_lock(&mutexed);
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);

    Process *status;
    status = (Process *) malloc(sizeof(*status));
    (*status).pid = 150;
    pthread_mutex_unlock(&mutexed);
    pthread_exit((void *) status);
}


//thread scheduling

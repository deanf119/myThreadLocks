/**
 * Lab #2
 * 
 * Developers:
 * 1) Dean Fernandes
 *      301274908
 *      deanf@sfu.ca
 * 2) Sheel Soneji
 *      301295318
 *      ssoneji@sfu.ca
 * 
 * Purpose: Test 3 different locks by spawning a large number of threads 
 *          and forcing them to enter a door at once.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_THREADS 200
bool all_threads_are_created = false;
pthread_mutex_t lock; 
int threadCount = 0;
bool testLockArray[MAX_THREADS];




/**
 * Tasks:
 * 
 * Launch 1000 threads      -
 * Pthread lock             -
 * Boolean Array Lock       -
 * Ticket Lock              -
 * 
 * 
*/

void mythread_launch_pthreadLock();
void mythread_launch_arrayLock();
void mythread_launch_ticketLock();

void* pthreadLock_test(void* arg);
void* arrayLock_test(void* arg);
void* ticketLock_test(void* arg);

void method1();
void method2();
void method3();


int main(){

    //method1();
    method2();
    //method3();

    
    return 0;
}

void method1(){
    printf("--------------------------------------Method#1--------------------------------------\n");
    all_threads_are_created = false;
    threadCount = 0;
    mythread_launch_pthreadLock();
}
void method2(){
    printf("--------------------------------------Method#2--------------------------------------\n");
    all_threads_are_created = false;
    threadCount = 0;
    mythread_launch_arrayLock();
}
void method3(){
    printf("--------------------------------------Method#3--------------------------------------\n");
    all_threads_are_created = false;
    threadCount = 0;
    mythread_launch_ticketLock();
}



void mythread_launch_pthreadLock(){

    pthread_t myThread_ID [MAX_THREADS]; //array for threads
    int currThread_Num[MAX_THREADS]; // current thread number


    for (int i=0; i<MAX_THREADS; i++){

        //current thread number
        currThread_Num[i]= i;

        //default thread attributes
        pthread_attr_t attr;
        pthread_attr_init (&attr); 

        //create thread
        pthread_create(&myThread_ID[i], &attr, pthreadLock_test, &currThread_Num[i]);
    }

    //all threads created
    all_threads_are_created = true;

    for (int i=0; i<MAX_THREADS; i++){
        //join thread
        pthread_join(myThread_ID[i], NULL);
    }

}


void* pthreadLock_test(void* arg){

    while (threadCount < MAX_THREADS && all_threads_are_created== true){

        pthread_mutex_lock(&lock);
        //CS
        threadCount++;
        printf("The number of threads in The CS is %d \n",threadCount);
        pthread_mutex_unlock(&lock);
        
    }
}


void mythread_launch_arrayLock(){

    pthread_t myThread_ID [MAX_THREADS]; //array for threads
    int currThread_Num[MAX_THREADS]; // current thread number

    for (int i=0; i<MAX_THREADS; i++){
        testLockArray[i]= false;
    }


    for (int i=0; i<MAX_THREADS; i++){

        //current thread number
        currThread_Num[i]= i;

        //default thread attributes
        pthread_attr_t attr;
        pthread_attr_init (&attr); 

        //create thread
        pthread_create(&myThread_ID[i], &attr, arrayLock_test, &currThread_Num[i]);
    }

    //initialize the array
    testLockArray[threadCount] = true;

    //all threads created
    all_threads_are_created = true;

    for (int i=0; i<MAX_THREADS; i++){
        //join thread
        pthread_join(myThread_ID[i], NULL);
    }

}

void* arrayLock_test(void* arg){
    
    int temp = *((int*)arg);
    printf("Reach before and %d\n",threadCount);


    while ((threadCount < MAX_THREADS) && (all_threads_are_created== true)){
        
        printf("Reach here and %d\n",temp);
        while(testLockArray[temp] == false){}
        //CS
        printf("The number of threads in The CS is %d \n",threadCount+1);
        testLockArray[threadCount++]=true;

    }    
}


void mythread_launch_ticketLock(){

    pthread_t myThread_ID [MAX_THREADS]; //array for threads
    int currThread_Num[MAX_THREADS]; // current thread number


    for (int i=0; i<MAX_THREADS; i++){

        //current thread number
        currThread_Num[i]= i;

        //default thread attributes
        pthread_attr_t attr;
        pthread_attr_init (&attr); 

        //create thread
        pthread_create(&myThread_ID[i], &attr, ticketLock_test, &currThread_Num[i]);
    }

    //all threads created
    all_threads_are_created = true;

    for (int i=0; i<MAX_THREADS; i++){
        //join thread
        pthread_join(myThread_ID[i], NULL);
    }

}

void* ticketLock_test(void* arg){
    
}
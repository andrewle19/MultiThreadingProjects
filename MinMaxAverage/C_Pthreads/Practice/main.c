//  Author: Andrew Le
//  Email: andrewle19@csu.fullerton.edu
//  grab a set of integers and find the min/max/average with multiple threads


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
// *a is a number set
int *a;
// global variables for max/min/avg
int max = INT_MIN;
int min = INT_MAX;
int avg = 0;

// avg number thread function
// calculates the avg of the numbers
void *avgNum(void *arg)
{
    int total = sizeof(arg)/sizeof(arg[0]);
    for (int i = 0; i < total-1; i++) {
        avg += a[i];
    }
    avg /= total-1;
    pthread_exit(0);
}


// max number thread function
// finds the max number in the number set
void *maxNum(void *arg)
{
    int total = sizeof(arg)/sizeof(arg[0]);
   
    for (int i = 0; i < total-1; i++) {
       
        if(a[i] > max){
            max = a[i];
        }
    }
    pthread_exit(0);
}

// max number thread function
// finds the max number in the number set
void *minNum(void *arg)
{
    int total = sizeof(arg)/sizeof(arg[0]);
    
    for (int i = 0; i < total-1; i++) {
        
        if(a[i] < min){
            min = a[i];
        }
    }
    pthread_exit(0);
}


int main(int argc, char * argv[]) {

    pthread_t thd1,thd2,thd3;
    // grab arguments and convert them to ints
    a = (int*)malloc(sizeof(int));
    for(int i = 1; i < argc; i++)
    {
        a[i-1] = atoi(argv[i]);
    }
    // if there is no arguments
    if(argc == 1){
        
        printf("No Arguments Entered\n");
        
        
    } // if there is only to arguemnts
    else if(argc == 2){
        int num = atoi(argv[1]);
        printf("The average value is %i \n", num);
        printf("The minimum value is %i \n", num);
        printf("The maximum value is %i \n", num);
    }
    // find the avarage/max/min values
    else{
        
        pthread_create(&thd1, NULL, maxNum, &a);
        pthread_create(&thd2, NULL, minNum, &a);
        pthread_create(&thd3, NULL, avgNum, &a);
        
        pthread_join(thd1,NULL);
        pthread_join(thd2, NULL);
        pthread_join(thd3, NULL);
        
        printf("The Average value is %i\n",avg);
        printf("The Minimum value is %i\n",min);
        printf("The Maximum value is %i\n",max);

    }
    
    
    

    return 0;
}

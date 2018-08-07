// Author: Andrew Le
// email: andrewle19@csu.fullerton.edu
// 10/15/17


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// defines the array size to 10
#define SIZE 10

// unsorted array
int a[] = {7,12,19,3,18,4,2,6,15,8};

// sorted array
int *b;

typedef struct index{
    int p;
    int r;
}index;



void *merge_sort(void * param) {
    
    
    index *pr = (index*) param;
    
    int p = pr->p, r = pr->r;
    
    if(p == r){
        pthread_exit(0);
    }
    
    // two sides of the thread sort
    int sort1,sort2;
    // declare two threads
    pthread_t thd1,thd2;
    // find the mid point of the array
    int mid = (pr->p + pr->r)/2;
    // indexs for each side of the array
    index side1,side2;
    // spliting the array indexs in 2
    side1.p = pr->p;
    side1.r = mid;
    side2.p = mid+1;
    side2.r = pr->r;
    
    // create thread to sort half of the array
    sort1 = pthread_create(&thd1, NULL, merge_sort,(void*)&side1);
    if(sort1 >0){
        printf("Failed to create new thread1\n");
    }
    
    // create thread to sort other half
    sort2 = pthread_create(&thd2, NULL, merge_sort,(void*)&side2);
    if(sort2 >0){
        printf("Failed to create new thread2\n");
    }
    
    // join the threads
    pthread_join(thd1, NULL);
    pthread_join(thd2, NULL);
    
    
    int k = pr->p;
    int i = pr->p;
    int j = mid+1;
    
    // MERGE SORT ALGORITHM
    while(i <= mid && j <= r){
        
        if(a[i] < a[j]){
            b[k] = a[i];
            k++;
            i++;
        } else {
            b[k] = a[j];
            k++;
            j++;
        }
        
    }
    for (; i<=mid ; i++) {
         b[k] = a[i];
         k++;
    }
    
    for (; j<=r ; j++){
        b[k] = a[j];
        k++;
    }
    
    for (i= pr->p ; i <= r ;i++) {
        a[i] = b[i];
    }
    
    
    pthread_exit(0);
    return NULL;
}

int main() {
    
    // make a parent thread
    pthread_t start_thread;
    b = (int*)malloc(sizeof(int)*SIZE);
    
    // start index
    index start;
    start.p = 0;
    start.r = SIZE-1;
    
    // print before the sort
    printf("Before Sort: ");
    for(int i = 0; i < SIZE; i++){
        printf("%i ",a[i]);
    }
    printf("\n");
    
    // create thread to merge sort
    pthread_create(&start_thread, NULL, merge_sort, &start);
    pthread_join(start_thread,NULL);
    
    // print after the sort
    printf("After Sort: ");
    for(int i = 0; i < SIZE; i++){
        printf("%i ",a[i]);
    }
    printf("\n");
    
    return 0;
}

//
//  main.c
//  threads_ch4
////
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


size_t global_positives = 0;
typedef struct list {   // typedef list as struct list*
    struct list* next;
    double val;
} * list;

typedef struct {
    list li;
    unsigned int sleep_us;
} sleeplist;

void showprogress(char c, unsigned int sleep_us) {
    printf("%c", c);
    fflush(stdout);
    usleep(sleep_us);
}
//============================================================================================
void count_positives(list l, unsigned int sleep_us) {
    list p;
    for (p = l; p != NULL; p = p->next) {
        if (p->val > 0.0) {
          printf("%f\n",p->val );
          ++global_positives;
        }  // global_positives = global_positives + 1;
        showprogress('*', 90000);
    }
}
void count_positives_register(list li, unsigned int sleep_us) {
    register long r = global_positives;
    list p = li;
    for (p = li; p != NULL; p = p->next) {
        if (p->val > 0.0) { ++r; }
        showprogress('*', 90000);
    }
    global_positives = r;
}
void* count_positives_runner(void* params) {
    sleeplist* psli = (sleeplist*)params;
    count_positives(psli->li, psli->sleep_us);
    //count_positives_register(psli->li, psli->sleep_us);
    return NULL;
}
//============================================================================================
void* incr_positives_runner(void* params) {
    unsigned int sleep_us = *(unsigned int*)params;
    for (int i = 0; i < 3; ++i) {       // no multiple statements on one line;  do not copy this style
        showprogress('.', 90000);
        // this code was adding the 3 global positives++global_positives;
    }
    return NULL;
}

#define VALUES 18

int test_count_positives() {
    list li = NULL;
    size_t size = 0;
    int result = 0;
    double* vals = (double*)malloc(VALUES * sizeof(double));

    for (int i = 0; i < VALUES; ++i) {
        vals[i] = -(2 * i + 1);
    }

//    double vals[] = { -1.0, -3.0, -5.0, -7.0, -9.0, -11.0, -13.0, -15.0, -17.0, -19.0, -21.0, -23.0, -25.0, -27.0, -29.0,
//        -31.0, -33.0, -35.0 };              // init list
    for (int i = 0; i < VALUES; ++i) {
        list newnode = (list)malloc(sizeof(struct list));
        newnode->next = li;
        newnode->val = vals[i];
        li = newnode;
        ++size;
        printf("%f ", li->val);
    }
    sleeplist sli;
    sli.li = li;    // this is a pointer
    sli.sleep_us = 90000;   // add 90,000 us sleep time to sleeplist to pass to thread A

    unsigned int sleep_us = sli.sleep_us;     // add same to pass to thread B

//        count_positives(li);                  // test list init
//        printf("global_positives is: %zu\n", global_positives);

    pthread_t pidtA;
    pthread_t pidtB;
    pthread_attr_t attr;

    printf("threads about to start...\n");
    pthread_attr_init(&attr);
    pthread_create(&pidtB, &attr, incr_positives_runner, (void*)&sleep_us);
    pthread_create(&pidtA, &attr, count_positives_runner, (void*)&sli);

    printf("waiting for threads to join...\n");
    pthread_join(pidtA, NULL);
    pthread_join(pidtB, NULL);
    printf("...threads both joined\n");
    printf("global_positives is: %zu\n", global_positives);

    printf("\n\nfreeing vals...\n");
    printf("freeing list of nodes...\n");
    free(vals);
    while (li != NULL) {    // release list of nodes
        list p = li;
        li = li->next;
        free(p);
    }
    return result;
}

int myglobal = 0;

void* threadfn(void* arg) {
    int i, j;
    for (i = 0; i < 20; ++i) {
        j = myglobal;
        j = j + 1;
        showprogress('+', *(unsigned int*)arg);
        myglobal = j;
    }
    printf("\t\t\t");
    return NULL;
}

int thread2() {
    pthread_t mythread;
    int i;
    unsigned int sleep_us = 10000;
    if (pthread_create(&mythread, NULL, threadfn, (void*)&sleep_us)) {
        printf("error creating thread.\n");
        abort();
    }
//    printf("both threads will alternate activity with sleep for %u ms...\n", sleep_us/1000);
    for (i = 0; i < 20; ++i) {
        myglobal = myglobal + 1;
        showprogress('o', sleep_us);
    }
    if (pthread_join(mythread, NULL)) {
        printf("error joining thread.\n");
        abort();
    }
    printf("myglobal equals %d\n", myglobal);
    return 0;
}

int main(int argc, const char * argv[]) {
    int result;
   result = test_count_positives();
    //for (int i = 0; i < 50; ++i) { result = thread2(); myglobal = 0; }

    printf("\t\t...done.\n");
    return result;
}

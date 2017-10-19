//
//  thread_and_mainthread.c
//  threads_ch4
//
//

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void showprogress(char c, unsigned int sleep_us) {
    printf("%c", c);
    fflush(stdout);
    usleep(sleep_us);
}

int myglobal = 0;

typedef struct {
    size_t repeats;
    unsigned int sleep_us;
} uint_szt;


void* thread2fn(void* params) {
    uint_szt usz = *(uint_szt*)params;
    for (int i = 0, j = 0; i < usz.repeats; ++i) {
        j = myglobal;
        j = j + 1;
        showprogress('+', usz.sleep_us);
        myglobal = j;
    }
    printf("\t");
    return NULL;
}

#define REPEAT_TEST         25
#define REPEAT_INCREMENT    30
#define SLEEP_US            2500

void showResults(int i) {
    static int myprev = 0;

    printf("\tmyglobal equals  %2d", myglobal);
    if (myglobal - myprev != 0) { printf("\t %2d", myglobal - myprev); }
    myprev = myglobal;
    printf("%s\n", (i % 5 == 4 ? "\n" : ""));
}


int main(int argc, const char * argv[]) {
    pthread_t mythread;
    uint_szt usz;  usz.repeats = REPEAT_INCREMENT;  usz.sleep_us = SLEEP_US;
    for (int i = 0; i < REPEAT_TEST; ++i) {
        printf("test %2d\t", i);
        myglobal = 0;
        if (pthread_create(&mythread, NULL, thread2fn, (void*)&usz)) {  printf("error creating thread.\n");  abort();  }

        for (int i = 0; i < REPEAT_INCREMENT; ++i) {
            myglobal = myglobal + 1;    showprogress('o', SLEEP_US);
        }

        if (pthread_join(mythread, NULL)) {  printf("error joining thread.\n");  abort();  }

        showResults(i);
    }

    printf("\t\t...done.\n");
    return 0;
}

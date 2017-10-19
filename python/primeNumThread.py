#!/usr/bin/python
#Author: Andrew Le and Andrew Rivada
#email: andrewle19@csu.fullerton.edu
# MultiThreaded Prime Numbers
import logging
import threading
import time
import sys


def primeNumWorker(x):
    """ thread worker to print prime nums less than argument passed"""
    endrange = int(x)+1
    for num in range(1,endrange):
        prime = True
        for i in range(2,num):
            if (num%i==0):
                prime = False
        if prime:
            print(num, sep=' ',end=' ',flush=True)
    print('\n')
    return


if(len(sys.argv) == 1):
    print("Usage error no integer argument inputed")
elif(len(sys.argv) == 2):
    print("PrimeNumbers")
    t = threading.Thread(target=primeNumWorker,args=(sys.argv[1],))
    t.start()
    t.join()
else:
    print("Usage error too many arguments")

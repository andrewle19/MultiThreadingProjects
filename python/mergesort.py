#!/usr/bin/python
#Author: Andrew Le and Andrew Rivada
#email: andrewle19@csu.fullerton.edu
# MultiThreaded Merge Sort
import logging
from threading import Thread
import time

# Python program for implementation of MergeSort

# Merges two subarrays of arr[].
# First subarray is arr[l..m]
# Second subarray is arr[m+1..r]
def merge(arr, l, m, r):
    n1 = int(m - l + 1)
    n2 = int(r - m)


    # create temp arrays
    L = [0] * int(n1)
    R = [0] * int(n2)

    # Copy data to temp arrays L[] and R[]
    for i in range(0 , n1):
        L[i] = arr[int(l + i)]

    for j in range(0 , n2):
        R[j] = arr[int(m + 1 + j)]

    # Merge the temp arrays back into arr[l..r]
    i = 0     # Initial index of first subarray
    j = 0     # Initial index of second subarray
    k = int(l)     # Initial index of merged subarray

    while i < n1 and j < n2 :
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    # Copy the remaining elements of L[], if there
    # are any
    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    # Copy the remaining elements of R[], if there
    # are any
    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1

# l is for left index and r is right index of the
# sub-array of arr to be sorted
def mergeSort(arr,l,r):
    if l < r:

        # Same as (l+r)/2, but avoids overflow for
        # large l and h
        m = int((l+(r-1))/2)

        # Sort first and second halves
        mergeSort(arr, l, m)
        mergeSort(arr, m+1, r)
        merge(arr, l, m, r)


# Driver code to test above
arr = [7,12,19,3,18,4,2,6,15,8];

mid = int(9/2)
n = len(arr)
print ("Given array is")
print (arr),

# create 2 threads for each side of array
thread1 = Thread(target=mergeSort,args=(arr,0,mid))
thread2 = Thread(target=mergeSort,args=(arr,mid+1,n-1))

# start the threads
thread1.start()
thread2.start()
# join them
thread1.join()
thread2.join()

# merge the result
merge(arr, 0, mid, n-1)

print ("\n\nSorted array is")
print (arr),

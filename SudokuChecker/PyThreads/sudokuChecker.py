#!/usr/bin/python
#Author: Andrew Le 
#email: andrewle19@csu.fullerton.edu
# MultiThreaded Sudoku Checker
import logging
from threading import Thread
import time


# the number of rows and columns for sudoku
COLUMNNUM = 9
ROWNUM = 9

check = [0,0,0,0,0,0,0,0,0]
valid = [1,1,1,1,1,1,1,1,1,1,1]
sudoku = [
    [6, 2, 4, 5, 3, 9, 1, 8, 7],
    [5, 1, 9, 7, 2, 8, 6, 3, 4],
    [8, 3, 7, 6, 1, 4, 2, 9, 5],
    [1, 4, 3, 8, 6, 5, 7, 2, 9],
    [9, 5, 8, 2, 4, 7, 3, 6, 1],
    [7, 6, 2, 3, 9, 1, 4, 5, 8],
    [3, 7, 1, 9, 5, 6, 8, 4, 2],
    [4, 9, 6, 1, 8, 2, 5, 7, 3],
    [2, 8, 5, 4, 7, 3, 9, 1, 6]
    ]

# function to reset the check array
def resetCheck():
    for x in range(0,9):
        check[x] = 0
    return

# function to check the rows
def checkRows():

    # loop through rows checking if sudoku is valid
    for i in range(0,ROWNUM):
        resetCheck()
        for j in range(0,COLUMNNUM):

            index = sudoku[i][j]-1

            try:
                check[index] = sudoku[i][j]
            except:
                valid[0] = 0

            if(sudoku[i][j] < 1 or sudoku[i][j] > 9):

                valid[0] = 0

        for k in range(0,9):
            if(check[k] == 0):
                print(i,k)
                valid[0] = 0
    return


# function to check the columns
def checkColumns():

    # loop through columns checking if sudoku is valid
    for i in range(0,ROWNUM):
        resetCheck()
        for j in range(0,COLUMNNUM):
            index = sudoku[j][i]-1

            try:
                check[index] = sudoku[j][i]
            except:
                valid[1] = 0

            if(sudoku[j][i] < 1 or sudoku[j][i] > 9):
                valid[1] = 0

        for k in range(0,9):
            if(check[k] == 0):
                valid[1] = 0
    return

# check all nine by nine subsections
# parameters: starting row, ending row, starting columns, ending columns, threadnum
def checkSubSection(srow,row,scol,col,threadnum):

    resetCheck()
    for i in range(srow,row):
        for j in range(scol,col):

            index = sudoku[i][j]-1

            try:
                check[index] = sudoku[j][i]
            except:
                valid[threadnum] = 0

            if(sudoku[i][j] < 1 or sudoku[i][j] > 9):
                valid[threadnum] = 0

    # checking if all numbers are present
    for k in range(0,9):
        if(check[k] == 0):
            valid[threadnum] = 0



print("Check Threads about to start")
thrd1 = Thread(target=checkRows)
thrd2 = Thread(target=checkColumns)
thrd3 = Thread(target=checkSubSection,args=(0,3,0,3,2))
thrd4 = Thread(target=checkSubSection,args=(0,3,3,6,3))
thrd5 = Thread(target=checkSubSection,args=(0,3,6,9,4))
thrd6 = Thread(target=checkSubSection,args=(3,6,0,3,5))
thrd7 = Thread(target=checkSubSection,args=(3,6,3,6,6))
thrd8 = Thread(target=checkSubSection,args=(3,6,6,9,7))
thrd9 = Thread(target=checkSubSection,args=(6,9,0,3,8))
thrd10 = Thread(target=checkSubSection,args=(6,9,3,6,9))
thrd11 = Thread(target=checkSubSection,args=(6,9,6,9,10))

thrd1.start()
thrd2.start()
thrd3.start()
thrd4.start()
thrd5.start()
thrd6.start()
thrd7.start()
thrd8.start()
thrd9.start()
thrd10.start()
thrd11.start()

print("Waiting for threads to join")

thrd1.join()
thrd2.join()
thrd3.join()
thrd4.join()
thrd5.join()
thrd6.join()
thrd7.join()
thrd8.join()
thrd9.join()
thrd10.join()
thrd11.join()
print("ALL 11 Threads have joined")



correct = True
# check if solution is correct
for i in range(0,11):
    if(valid[i] == 0):
        correct = False


if(correct):
    print("Solution is valid")
else:
    print("Solution is not valid")

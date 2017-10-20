package com.ZDreams;

public class Main {

    static int[][] sudoku = {
            {6, 2, 4, 5, 3, 9, 1, 8, 7},
            {5, 1, 9, 7, 2, 8, 6, 3, 4},
            {8, 3, 7, 6, 1, 4, 2, 9, 5},
            {1, 4, 3, 8, 6, 5, 7, 2, 9},
            {9, 5, 8, 2, 4, 7, 3, 6, 1},
            {7, 6, 2, 3, 9, 1, 4, 5, 8},
            {3, 7, 1, 9, 5, 6, 8, 4, 2},
            {4, 9, 6, 1, 8, 2, 5, 7, 3},
            {2, 8, 5, 4, 7, 3, 9, 1, 6}
    };
    static int[] valid = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    public static void resetCheck(int array[]) {
        for (int i = 0; i < 9; i++) {
            array[i] = 0;
        }
    }


    // class to check row
    public static class checkRows implements Runnable {
        @Override
        public void run() {

            // check array to check 9 spots of column
            int check[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

            // loop through all the columns
            for (int i = 0; i < 9; i++) {
                resetCheck(check);

                for (int j = 0; j < 9; j++) {
                    // grab index of column
                    int index = sudoku[i][j] - 1;

                    // checks if the spots have a number from 0-9 if not then makes the solution invalid
                    if (sudoku[i][j] < 1 || sudoku[i][j] > 9) {
                        valid[0] = 0;
                    }
                    else{
                        check[index] = sudoku[i][j];
                    }

                }

                // checks the check array to make sure check section has integers 0...9 if not solution invalid
                for (int k = 0; k < 9; k++) {
                    if (check[k] == 0) {
                        valid[0] = 0;
                    }
                }

            }
        }
    }

    // class to check columns
    public static class checkColumns implements Runnable {
        @Override
        public void run() {

            // check array to check 9 spots of column
            int check[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

            // loop through all the columns
            for (int i = 0; i < 9; i++) {
                resetCheck(check);

                for (int j = 0; j < 9; j++) {
                    // grab index of column
                    int index = sudoku[j][i] - 1;

                    // checks if the spots have a number from 0-9 if not then makes the solution invalid
                    if (sudoku[j][i] < 1 || sudoku[j][i] > 9) {
                        valid[1] = 0;
                    }
                    else{
                        check[index] = sudoku[j][i];
                    }

                }

                // checks the check array to make sure check section has integers 0...9 if not solution invalid
                for (int k = 0; k < 9; k++) {
                    if (check[k] == 0) {
                        valid[1] = 0;
                    }
                }

            }
        }
    }


    public static class checkSubsections implements Runnable {

        int srow,row,scol,col,threadnum;
        checkSubsections(int startrow, int erow, int startcol, int ecol,int num){
            srow = startrow;
            row = erow;
            scol = startcol;
            col = ecol;
            threadnum = num;
        }


        @Override
        public void run() {

            // check array to check 9 spots of column
            int check[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

            // loop through all the columns
            for (int i = srow; i < row; i++) {

                for (int j = scol; j < col; j++) {
                    // grab index of column
                    int index = sudoku[i][j] - 1;

                    // checks if the spots have a number from 0-9 if not then makes the solution invalid
                    if (sudoku[i][j] < 1 || sudoku[i][j] > 9) {
                        valid[threadnum] = 0;
                    } else {
                        check[index] = sudoku[i][j];
                    }

                }
            }
            // checks the check array to make sure check section has integers 0...9 if not solution invalid
            for (int k = 0; k < 9; k++) {
                if (check[k] == 0) {
                    valid[threadnum] = 0;
                }
            }


        }
    }


    public static void main(String[] args) {
        Thread []threads = new Thread[11];
        boolean correct = true;
        System.out.println("Threads Created");
        threads[0] = new Thread(new checkRows());
        threads[1] = new Thread(new checkColumns());
        threads[2] = new Thread(new checkSubsections(0,3,0,3,2));
        threads[3] = new Thread(new checkSubsections(0,3,3,6,3));
        threads[4] = new Thread(new checkSubsections(0,3,6,9,4));

        threads[5] = new Thread(new checkSubsections(3,6,0,3,5));
        threads[6] = new Thread(new checkSubsections(3,6,3,6,6));
        threads[7] = new Thread(new checkSubsections(3,6,6,9,7));
        threads[8] = new Thread(new checkSubsections(6,9,0,3,8));
        threads[9] = new Thread(new checkSubsections(6,9,3,6,9));
        threads[10] = new Thread(new checkSubsections(6,9,6,9,10));


       System.out.println("Threads Starting up");
       for (int i = 0; i < 11; i++){
           threads[i].start();
       }

        System.out.println("Waiting for threads to join ");

        try {
            for (int i = 0; i < 11; i++) {
                threads[i].join();
            }
        } catch(InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Threads joining up ");

        for(int i = 0; i < 11; i++){
            if(valid[i] == 0){
                correct = false;
            }
        }
        if(correct){
            System.out.println("Solution is valid");
        }else{
            System.out.println("Solution is invalid");
        }
        System.exit(0);
    }
}

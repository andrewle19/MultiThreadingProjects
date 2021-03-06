// AUTHOR: Andrew Le 
// EMAIL: andrewle19@csu.fullerton.edu
// 10/17/17
// Monte Carlo Approximation of PI in omp
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <omp.h>
using namespace std;

// the count of the points inside the circle
int countInside = 0;
// the total points created
int TOTALPOINTS = 1000;


void RandomPoints()
{
    srand((unsigned int)time(NULL)); // generate random seet
    float x; // x cordinate
    float y; // y cordinate
    float d; // calculate if inside the line
    // loop to create random series of points
    for(int i = 0; i < TOTALPOINTS; i++){
        
        // generate random numbers between -1 to 1 for x and y cordinate
        x = ((float(rand()) / float(RAND_MAX)) * (1 + 1)) - 1;
        y = ((float(rand()) / float(RAND_MAX)) * (1 + 1)) - 1;
        
        // calculate d to see if in the circle
        d = pow(x,2) + pow(y,2);
        d = sqrt(d);
        
        // check if the point is in the circle and increment count when it is
        if(d <= 1)
        {
            countInside += 1;
        }
    }
}

int main()
{
    float pi;
 
    #pragma omp for
    for(int i = 0; i < 1; i++){
    	    RandomPoints();
	}
    
	
   // approximate pi
    pi = 4 * (static_cast<float>(countInside)/static_cast<float>(TOTALPOINTS));
    cout << "Number of points inside the circle: " << countInside << endl;
    cout << "The Monte Carlo Approximation of PI: " << pi << endl;
    return 0;
}



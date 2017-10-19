#include <iostream>
#include <omp.h>
using namespace std;

// g++ omp.cpp

int main(int argc, char *arg[]){
	// sequential code
	#pragma omp parallel
	{
		cout << "I am a parrallel region" << endl;
	}
	// sequential code
		return 0;
}

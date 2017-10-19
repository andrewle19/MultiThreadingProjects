#include <omp.h>
#include <stdio.h>

// gcc -fopnmp <file name> -o <output>

int main(int argc, char *arg[]){
	// sequential code 
	#pragma omp parallel
	{
		print("I am a parrallel region\n")
	}
	// sequential code
		0;
}


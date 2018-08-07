//Andrew Le
//andrewrivada@csu.fullerton.edu

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

void merge_arr(int * X, int n, int * tmp) // merge both arrays  
{
	int i = 0;
	int j = n / 2;
	int ti = 0;

	while ( i<n / 2 && j<n) {
		if (X[i] < X[j]) {
			tmp[ti] = X[i];
			ti++; i++;
		}
		else {
			tmp[ti] = X[j];
			ti++; j++;
		}
	}
	while (i<n / 2) { //complete the upper half
		tmp[ti] = X[i];
		ti++; i++;
	}
	while (j<n) { //complete the lower half
		tmp[ti] = X[j];
		ti++; j++;
	}
	memcpy(X, tmp, n * sizeof(int));
} 

void merge_sort(int * X, int n, int * tmp)// recursive merge sort with threads
{
	if (n < 2) return;

#pragma omp task firstprivate (X, n, tmp)
	merge_sort(X, n / 2, tmp);

#pragma omp task firstprivate (X, n, tmp)
	merge_sort(X + (n / 2), n - (n / 2), tmp);

#pragma omp taskwait // waits till threads finish 

	// merge both halves back together
	merge_arr(X, n, tmp);
}


int main()
{
	int n = 10;
	int data[] = { 9,3,5,4,78,23,1,3,0,45};
	int tmp[10];

	printf("List Before Sorting...\n");
	for (int j = 0; j < n; j++) {
		printf("%d ", data[j]);
	}

#pragma omp parallel // begin merge sort
	{
	#pragma omp single
		merge_sort(data, n, tmp);
	}

	printf("\nList After Sorting...\n");
	for (int j = 0; j < n; j++){
		printf("%d ", data[j]);
	}
}

/*
 * Fenwick Tree Range update, Point query test file
 * A Fenwick tree implementation which supports range updates and point queries
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#include "fenwickTree.h"

// Test
void fenwickTreeTest();

// Test driver code
int main(int argc, char* argv[]){

	// run the test
	fenwickTreeTest();

	return 0;
}

// Fenwick tree test
void fenwickTreeTest(){
	// Size of the array 
	int size = 7;

	// init an array and init index 0 to 0
	long testArray[] = {0, 1, -2, 3, -4, 5, -6};
	testArray[0] = 0;

	// Setting up random number
/*	srand(time(NULL));
	for (int i = 1; i < size; i++)
	{
		// Generate a random num for length of the string
		int num = (int)((((float)rand() / (float)(RAND_MAX)) * 86) - 7);
		// add random num to array
		//testArray[i] = num;
	}
		
*/
	// Print the test array
	printf("input array data: \n");
	for(int i = 1; i < size; i++){
		printf("index: %d	data: %ld\n", i, testArray[i]);
	}

	// Setup Fenwick tree
	struct FenwickTree ft;

	// init Fenwick tree
	fenwickTreeInit(&ft, testArray, size);

	// Add +10 to interval [1, 4] in O(log(n))
	printf("\nUpdate range [1, 4] +10\n");
	fenwickTreeUpdateRange(&ft, 1, 4, 10);

	// Get values at specific index after update
	printf("Get value at index 1: %ld\n", fenwickTreeGet(&ft, 1)); // 11
	printf("Get value at index 4: %ld\n", fenwickTreeGet(&ft, 4)); // 6
	printf("Get value at index 5: %ld\n", fenwickTreeGet(&ft, 5)); // 5

	// Add -20 to interval [3, 6] in O(log(n))
	printf("\nUpdate range [3, 6] -20\n");
	fenwickTreeUpdateRange(&ft, 3, 6, -20);

	// Get values at specific index after update
	printf("Get value at index 3: %ld\n", fenwickTreeGet(&ft, 3)); // -7
	printf("Get value at index 4: %ld\n", fenwickTreeGet(&ft, 4)); // -14
	printf("Get value at index 5: %ld\n", fenwickTreeGet(&ft, 5)); // -15
	

	// Print data from the fenwick tree
	printf("\nFenwick tree data: \n\n");
	fenwickTreePrint(&ft);

	// Clen up memory
	fenwickTreeClear(&ft);
}


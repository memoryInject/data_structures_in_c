/*
 * Fenwick Tree Range Query, Point Update test file
 * A Fenwick tree implementation which supports updates and sum range queries
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
	int size = 17;

	// init an array and init index 0 to 0
	long testArray[] = {0, 3, 5, -2, 4, 5, 21, 65, 8, 10, 4, 2, 1, 6, 5, 6, 24};
	testArray[0] = 0;

	// Setting up random number
	/*srand(time(NULL));
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

	// Prefix sum of 5 elements
	printf("\nPrefix sum of 5 elements: %ld\n", fenwickTreePrefixSum(&ft, 5));

	// Sum between index 5 and 12
	printf("Sum between index 5 and 12: %ld\n", fenwickTreeSum(&ft, 5, 12));

	// Add 5 to index 7
	testArray[7] += 5;

	// point update FenwickTree
	fenwickTreeAdd(&ft, 7, 5);
	
	// Print the test array
	printf("\ninput array data after update index 7 +5: \n");
	for(int i = 1; i < size; i++){
		printf("index: %d	data: %ld\n", i, testArray[i]);
	}

	// Sum between index 5 and 12
	printf("Sum between index 5 and 12 after update: %ld\n", fenwickTreeSum(&ft, 5, 12));

	// Print data from the fenwick tree
	printf("\nFenwick tree data: \n");
	fenwickTreePrint(&ft);

	// Clen up memory
	fenwickTreeClear(&ft);
}


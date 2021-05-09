#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>


#include "../fenwickTree.h"
#include "unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

// initialize size for array
#define ARRAY_SIZE 7

// Initialize global array of size ARRAY_SIZE for Fenwick tree test
long testArray[] = {0, 1, -2, 3, -4, 5, -6};

void test_function_fenwickTreeConstruction(void){

	// Print the test array
	printf("input array data: \n");
	for(int i = 1; i < ARRAY_SIZE; i++){
		printf("index: %d	data: %ld\n", i, testArray[i]);
	}

	// Setup Fenwick tree
	// init Fenwick tree
	struct FenwickTree* ft = fenwickTreeInit(testArray, ARRAY_SIZE);
	
	// Print data from the fenwick tree
	printf("\nFenwick tree data: \n");
	fenwickTreePrint(ft);

	// Clen up memory
	fenwickTreeClear(ft);
}

void test_function_fenwickTreeTest(void){
	// Setup Fenwick tree
	// init Fenwick tree
	struct FenwickTree* ft = fenwickTreeInit(testArray, ARRAY_SIZE);

	// Add +10 to interval [1, 4] in O(log(n))
	printf("\nUpdate range [1, 4] +10\n");
	fenwickTreeUpdateRange(ft, 1, 4, 10);

	// Get values at specific index after update
	TEST_ASSERT_EQUAL(fenwickTreeGet(ft, 1), 11);
	TEST_ASSERT_EQUAL(fenwickTreeGet(ft, 4), 6);
	TEST_ASSERT_EQUAL(fenwickTreeGet(ft, 5), 5);

	// Print data from the fenwick tree
	printf("\nFenwick tree data: \n\n");
	fenwickTreePrint(ft);

	// Clen up memory
	fenwickTreeClear(ft);
}


int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_fenwickTreeConstruction);
	RUN_TEST(test_function_fenwickTreeTest);
	return UNITY_END();
}


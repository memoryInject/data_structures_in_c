#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>


#include "fenwickTree.h"
#include "unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

// initialize size for array
#define ARRAY_SIZE 17

// Initialize global array of size ARRAY_SIZE for Fenwick tree test
long testArray[] = {0, 3, 5, -2, 4, 5, 21, 65, 8, 10, 4, 2, 1, 6, 5, 6, 24};

void test_function_fenwickTreeConstruction(void){

	// Print the test array
	printf("input array data: \n");
	for(int i = 1; i < ARRAY_SIZE; i++){
		printf("index: %d	data: %ld\n", i, testArray[i]);
	}

	// Setup Fenwick tree
	struct FenwickTree ft;

	// init Fenwick tree
	fenwickTreeInit(&ft, testArray, ARRAY_SIZE);
	
	// Print data from the fenwick tree
	printf("\nFenwick tree data: \n");
	fenwickTreePrint(&ft);

	// Clen up memory
	fenwickTreeClear(&ft);
}

void test_function_fenwickTreePrefixSum(void){
	// Setup Fenwick tree
	struct FenwickTree ft;

	// init Fenwick tree
	fenwickTreeInit(&ft, testArray, ARRAY_SIZE);

	// Prefix sum of 5 elements
	long ftSum =  fenwickTreePrefixSum(&ft, 5);
	printf("\nPrefix sum of 5 elements: %ld\n", ftSum);

	// check the sum of 5 elements in the testArray
	long sum = 0;
	for(int i = 1; i < 6; i++){
		sum += testArray[i];
	}

	TEST_ASSERT_EQUAL(sum, ftSum);

	// Clen up memory
	fenwickTreeClear(&ft);
}

void test_function_fenwickTreeSum(void){
	// Setup Fenwick tree
	struct FenwickTree ft;

	// init Fenwick tree
	fenwickTreeInit(&ft, testArray, ARRAY_SIZE);
	
	// Sum between index 5 and 12
	int start = 5;
	int end = 12;
	long ftSum =  fenwickTreeSum(&ft, start, end);
	printf("\nSum between index %d and %d: %ld\n", start, end, ftSum);


	// check the sum between 5 and 12 elements in the testArray
	long sum = 0;
	for(int i = start; i < end+1; i++){
		sum += testArray[i];
	}

	TEST_ASSERT_EQUAL(sum, ftSum);

	// Clen up memory
	fenwickTreeClear(&ft);
}

void test_function_fenwickTreeAdd(void){
	// Setup Fenwick tree
	struct FenwickTree ft;

	// init Fenwick tree
	fenwickTreeInit(&ft, testArray, ARRAY_SIZE);

	// Add 5 to index 7
	int index = 7;
	int add = 5;
	testArray[7] += add;

	printf("\nAdded %d to index %d\n", add, index);

	// point update FenwickTree
	fenwickTreeAdd(&ft, 7, 5);
	
	// Sum between index 5 and 12
	int start = 5;
	int end = 12;
	long ftSum =  fenwickTreeSum(&ft, start, end);
	printf("Sum between index %d and %d after added %d: %ld\n", start, end, add, ftSum);


	// check the sum after added between 5 and 12 elements in the testArray
	long sum = 0;
	for(int i = start; i < end+1; i++){
		sum += testArray[i];
	}

	TEST_ASSERT_EQUAL(sum, ftSum);

	// Clen up memory
	fenwickTreeClear(&ft);
}


int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_fenwickTreeConstruction);
	RUN_TEST(test_function_fenwickTreePrefixSum);
	RUN_TEST(test_function_fenwickTreeSum);
	RUN_TEST(test_function_fenwickTreeAdd);
	return UNITY_END();
}


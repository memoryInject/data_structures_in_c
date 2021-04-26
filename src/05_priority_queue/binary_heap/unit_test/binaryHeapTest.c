#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../binaryHeap.h"
#include "../../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_binaryHeapInit(void){
	// Initialize binary heap with capacity of 5 element
	struct BinaryHeap* bh = binaryHeapInit(5);

	// Add an element to binary heap
	binaryHeapAdd(bh, 3);
	binaryHeapAdd(bh, 5);
	binaryHeapAdd(bh, 1);
	binaryHeapAdd(bh, 8);
	binaryHeapAdd(bh, 2);
	
	TEST_ASSERT_EQUAL(binaryHeapIsActive(bh), true);
	TEST_ASSERT_EQUAL(binaryHeapSize(bh), 5);
	TEST_ASSERT_EQUAL(binaryHeapIsEmpty(bh), false);

	// Deallocate memory for heap
	binaryHeapClear(bh); 
}

void test_function_binaryHeapAdd(void){
	// Initialize binary heap with capacity of 5 element
	struct BinaryHeap* bh = binaryHeapInit(5);

	// Add an element to binary heap
	binaryHeapAdd(bh, 3);
	binaryHeapAdd(bh, 5);
	binaryHeapAdd(bh, 1);
	binaryHeapAdd(bh, 8);
	binaryHeapAdd(bh, 2);
	binaryHeapPoll(bh);
	
	TEST_ASSERT_EQUAL(binaryHeapIsActive(bh), true);
	TEST_ASSERT_EQUAL(binaryHeapSize(bh), 4);
	TEST_ASSERT_EQUAL(binaryHeapIsEmpty(bh), false);
	TEST_ASSERT_EQUAL(bh->heap[0], 2);
	TEST_ASSERT_EQUAL(bh->heap[1], 5);
	TEST_ASSERT_EQUAL(bh->heap[2], 3);
	TEST_ASSERT_EQUAL(bh->heap[3], 8);
	TEST_ASSERT_EQUAL(binaryHeapIsMinHeap(bh, 0), true);
	TEST_ASSERT_EQUAL(binaryHeapPoll(bh), 2);
	// Deallocate memory for heap
	binaryHeapClear(bh); 
}

void test_function_binaryHeapRemove(void){
	// Initialize binary heap with capacity of 5 element
	struct BinaryHeap* bh = binaryHeapInit(5);

	// Add an element to binary heap
	binaryHeapAdd(bh, 3);
	binaryHeapAdd(bh, 5);
	binaryHeapAdd(bh, 1);
	binaryHeapAdd(bh, 8);
	binaryHeapAdd(bh, 2);
	
	TEST_ASSERT_EQUAL(binaryHeapIsActive(bh), true);
	TEST_ASSERT_EQUAL(binaryHeapSize(bh), 5);
	TEST_ASSERT_EQUAL(binaryHeapIsEmpty(bh), false);
	TEST_ASSERT_EQUAL(binaryHeapIsMinHeap(bh, 0), true);
	TEST_ASSERT_EQUAL(binaryHeapPoll(bh), 1);
	TEST_ASSERT_EQUAL(binaryHeapRemoveAt(bh, 1), 5);
	TEST_ASSERT_EQUAL(binaryHeapRemove(bh, 3), true);
	TEST_ASSERT_EQUAL(binaryHeapRemove(bh, 10), false);

	// Deallocate memory for heap
	binaryHeapClear(bh); 
}
int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_binaryHeapInit);
	RUN_TEST(test_function_binaryHeapAdd);
	return UNITY_END();
}


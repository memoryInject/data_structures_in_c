#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../indexedBinaryHeap.h"
#include "../../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_indexedBinaryHeap(void){

	// Test array of names and the index of array is the 'ki'
	int n = 12;

	char** names = (char**) malloc(sizeof (char[10]) * n);
	names[0] = "Anna";
	names[1] = "Bella";
	names[2] = "Carly";
	names[3] = "Dylan";
	names[4] = "Emily";
	names[5] = "Fred";
	names[6] = "George";
	names[7] = "Henry";
	names[8] = "Isaac";
	names[9] = "James";
	names[10] = "Kelly";
	names[11] = "Laura";

	// Setup Indexed Binary Heap
	struct IdxBinaryHeap* ibh = idxBinaryHeapInit(n);	

	// names index as key index here (ki), and assign random values
	idxBinaryHeapInsert(ibh, 0, 3);
	idxBinaryHeapInsert(ibh, 1, 15);
	idxBinaryHeapInsert(ibh, 2, 11);
	idxBinaryHeapInsert(ibh, 3, 17);
	idxBinaryHeapInsert(ibh, 4, 7);
	idxBinaryHeapInsert(ibh, 5, 9);
	idxBinaryHeapInsert(ibh, 6, 2);
	idxBinaryHeapInsert(ibh, 7, 1);
	idxBinaryHeapInsert(ibh, 8, 6);
	idxBinaryHeapInsert(ibh, 9, 5);
	idxBinaryHeapInsert(ibh, 10, 16);
	idxBinaryHeapInsert(ibh, 11, 4);
	
	idxBinaryHeapPrint(ibh);
	idxBinaryHeapPrintTree(ibh);
	
	TEST_ASSERT_EQUAL(idxBinaryHeapIsActive(ibh), true);
	TEST_ASSERT_EQUAL(idxBinaryHeapSize(ibh), n);
	TEST_ASSERT_EQUAL(idxBinaryHeapIsEmpty(ibh), false);
	TEST_ASSERT_EQUAL(idxBinaryHeapPeekMinValue(ibh), 1);
	TEST_ASSERT_EQUAL(idxBinaryHeapPeekMinKeyIndex(ibh), 7);

	TEST_ASSERT_EQUAL(idxBinaryHeapPollMinKeyIndex(ibh), 7);
	TEST_ASSERT_EQUAL(idxBinaryHeapPeekMinKeyIndex(ibh), 6);

	TEST_ASSERT_EQUAL(idxBinaryHeapPollMinValue(ibh), 2);

	idxBinaryHeapDecrease(ibh, 8, 1);
	TEST_ASSERT_EQUAL(idxBinaryHeapPeekMinKeyIndex(ibh), 8);

	idxBinaryHeapIncrease(ibh, 8, 21);
	TEST_ASSERT_EQUAL(idxBinaryHeapValueOf(ibh, 8), 21);

	TEST_ASSERT_EQUAL(idxBinaryHeapDelete(ibh, 8), 21);
	
	TEST_ASSERT_EQUAL(names[idxBinaryHeapPeekMinKeyIndex(ibh)], "Anna");

	// Clear memory
	idxBinaryHeapClear(ibh);

	// Clear name array
	free(names);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_indexedBinaryHeap);
	return UNITY_END();
}


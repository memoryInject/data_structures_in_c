// Test code for indexed priority queue

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "indexedBinaryHeap.h"

void test();

int main(int argc, char* argv[]){
	test();
	return 0;
}

// Test driver code
void test(){
	// Create a bi-directional map with index and key, the index of this
	// map is called key index, 'ki'
	// for this test we skip the map, but only create an array with 'ki'	
	// Total length of the array
	int n = 12;
	
	// Setup Indexed Binary Heap
	struct IdxBinaryHeap* ibh = idxBinaryHeapInit(n);	

	// Setting up random number
	srand(time(NULL));
	for (int i = 0; i < n-1; i++){
		int value = (int)((((float)rand() / (float)(RAND_MAX)) * 86) + 5);
		// printf("%d ", num);
		// add random value each 'ki'
		idxBinaryHeapInsert(ibh, i, value);
	}

	// Insert value 111 at key index 11
	idxBinaryHeapInsert(ibh, 11, 111);

	idxBinaryHeapPrint(ibh);
	idxBinaryHeapPrintTree(ibh);

	// Size of the heap
	printf("Size: %d\n", idxBinaryHeapSize(ibh));

	// Peek min value in the heap
	int peekMinVal = idxBinaryHeapPeekMinValue(ibh);
	printf("Peak Min Value: %d\n", peekMinVal);

	// Peek min key index in the heap
	int peekMinKeyIdx = idxBinaryHeapPeekMinKeyIndex(ibh);
	printf("Peak Min Key Index: %d\n", peekMinKeyIdx);

	// Poll min key index 
	printf("Poll Min Key Index: %d\n", idxBinaryHeapPollMinKeyIndex(ibh));

	// Print Indexed Binary Heap
	idxBinaryHeapPrint(ibh);
	idxBinaryHeapPrintTree(ibh);

	printf("Size: %d\n", idxBinaryHeapSize(ibh));

	// Clear memory
	idxBinaryHeapClear(ibh);
}


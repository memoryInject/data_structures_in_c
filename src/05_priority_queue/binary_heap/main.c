#include <stdio.h>

#include "binaryHeap.h"

// Driver code for test
int main(int argc, char* argv[])
{
	// Initialize binary heap with capacity of 5 element
	struct BinaryHeap* bh = binaryHeapInit(5);

	// Add an element to binary heap
	binaryHeapAdd(bh, 3);
	binaryHeapAdd(bh, 5);
	binaryHeapAdd(bh, 1);
	binaryHeapAdd(bh, 8);
	binaryHeapAdd(bh, 2);
	binaryHeapPoll(bh);

	for (int i=0; i<bh->size; i++){	
		printf("Test data: %d\n", (bh->heap[i]));
	}
	
	printf("Is min heap ? : %s\n", binaryHeapIsMinHeap(bh, 0) == 1 ? "true" : "false");

	// Deallocate memory for heap
	binaryHeapClear(bh);
	printf("Dealllocate heap memory..\n");

	return 0;
}

#include <stdio.h>

#include "binaryHeap.h"

// Driver code for test
int main(int argc, char* argv[])
{
	// Create a binary heap struct
	struct BinaryHeap bh;

	// Initialize binary heap with capacity of 5 element
	binaryHeapInit(&bh, 5);

	// Add an element to binary heap
	binaryHeapAdd(&bh, 3);
	binaryHeapAdd(&bh, 5);
	binaryHeapAdd(&bh, 1);
	binaryHeapAdd(&bh, 8);
	binaryHeapAdd(&bh, 2);
	binaryHeapPoll(&bh);

	for (int i=0; i<bh.size; i++){	
		printf("Test data: %d\n", (bh.heap[i]));
	}
	
	printf("Is min heap ? : %s\n", binaryHeapIsMinHeap(&bh, 0) == 1 ? "true" : "false");

	return 0;
}

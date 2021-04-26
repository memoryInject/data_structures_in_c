/*
 * A min priotity queue implementaion using a binary heap
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "binaryHeap.h"

// Initialize binary heap with max capacity it will activate heap
struct BinaryHeap* binaryHeapInit(int capacity){
	struct BinaryHeap* bh = (struct BinaryHeap*) malloc(sizeof(struct BinaryHeap));
	bh->size = 0;
	bh->capacity = capacity;
	// Set array with capacity
	bh->heap = (int*) malloc(sizeof(int) * capacity);
	// Activate Binary Heap
	bh->state = true;

	return bh;
}

// Check if the current binary heap is active
bool binaryHeapIsActive(struct BinaryHeap* bh){
	return bh->state;
}

// Error handling if the binary heap is inactive
void binaryHeapState(struct BinaryHeap* bh){
	if(bh->state == false){
		printf("%s, inactive binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the size of binary heap.
int binaryHeapSize(struct BinaryHeap* bh){
	binaryHeapState(bh); // Check if the stack is active	
	return bh->size;
}

// Return the capacity of binary heap
int binaryHeapCapacity(struct BinaryHeap* bh){
	return bh->capacity;
}

// Check if the binary heap is empty
bool binaryHeapIsEmpty(struct BinaryHeap* bh){
	binaryHeapState(bh);
	if(bh->size == 0){
		return true;
	}
	else{
		return false;
	}
}

// Helper function swap two element
void binaryHeapSwap(struct BinaryHeap* bh, int i, int j){
	// Store value at heap array index i for swap
	int temp = bh->heap[i];
	// Change value at heap array index i to value at index j
	bh->heap[i] = bh->heap[j];
	// Change value at heap array index j to temp
	bh->heap[j] = temp;
}

// This function assume i & j are valid indices, O(1) // Helper function
bool binaryHeapLess(struct BinaryHeap* bh, int i, int j){
	int a = bh->heap[i];
	int b = bh->heap[j];
	return a<b ? true : false;
}

// Perform bottom up node swim, O(log(n))
void binaryHeapSwim(struct BinaryHeap* bh, int k){
	// Grab the index of the next parent node WRT to k
	int parent = (k - 1) / 2;
	// Keep swimmig while we have not reached the
	//	root and while we're less than our parent.
	while(k > 0 && binaryHeapLess(bh, k, parent)){
		// Exchange k with parent
		binaryHeapSwap(bh, parent, k);
		k = parent;

		// Grab the index of next parent node WRT to k
		parent = (k - 1) / 2;
	}
}

// Add an element to priority queue
void binaryHeapAdd(struct BinaryHeap* bh, int data){
	binaryHeapState(bh);
	if(bh->size < bh->capacity){
		bh->heap[bh->size] = data;
	}
	else{
		printf("Binary heap capacity is full!");
		exit(EXIT_FAILURE);
	}
	binaryHeapSwim(bh, bh->size);
	bh->size++;	
}

// Top down node sink, O(log(n))
void binaryHeapSink(struct BinaryHeap* bh, int k){
	while (true){
		int left = 2 * k + 1; // Left node
		int right = 2 * k + 2; // right node
		int smallest = left; // Assume left is the smallest node of the two children

		// Find which is smaller left or right
		// If right is smaller set smallest to right
		if(right < bh->size && binaryHeapLess(bh, right, left)){
			smallest = right;
		}

		// Stop if we are outside the bounds of the tree
		// or stop early if we can not sink k anymore
		if(left >= bh->size || binaryHeapLess(bh, k, smallest)){
			break;
		}

		// Move down the tree following the smallest node
		binaryHeapSwap(bh, smallest, k);
		k = smallest;
	}
}

// Remove a node at particular index, O(log(n))
int binaryHeapRemoveAt(struct BinaryHeap* bh, int i){
	binaryHeapState(bh);
	if(binaryHeapIsEmpty(bh)){
		printf("Binary heap is empty!\n");
		exit(EXIT_SUCCESS);
	}

	int data = bh->heap[i];
	--bh->size;
	binaryHeapSwap(bh, i, bh->size);

	// Oblitrate the value
	bh->heap[bh->size] = 0;

	// Check if the last element was removed
	if(i == bh->size){
		return data;
	}
	int elem = bh->heap[i];

	// Try sinking element
	binaryHeapSink(bh, i);

	// If sinking did not work try swimming
	if(bh->heap[i] == elem){
		binaryHeapSwim(bh, i);
	} 
	return data;
}

// Remove a particular element in the heap, O(n)
bool binaryHeapRemove(struct BinaryHeap* bh, int data){
	binaryHeapState(bh);
	// Linear removal via search, O(n)
	for(int i = 0; i < bh->size; i++){
		if(data == bh->heap[i]){
			binaryHeapRemoveAt(bh, i);
			return true;
		}
	}

	return false;
}

// Remove the root of the heap, O(log(n))
int binaryHeapPoll(struct BinaryHeap* bh){
	return binaryHeapRemoveAt(bh, 0);
}

// Recursively checks if this heap is a min heap
// Called this method with k=0 to start at the root
bool binaryHeapIsMinHeap(struct BinaryHeap* bh, int k){
	binaryHeapState(bh);
	// If we are outside the bound of the heap return true
	if(k >= bh->size){
		return true;
	}

	int left = 2 * k + 1;
	int right = 2 * k + 2;

	// Make sure that the current node k is less than 
	// both of it's children left and right if they exist
	// return false otherwise to indicate an invalid heap
	if(left < bh->size && !binaryHeapLess(bh, k, left)){
		return false;
	}
	if(right < bh->size && !binaryHeapLess(bh, k, right)){
		return false;
	}

	// Recurse on both children to make sure they're also valid heap
	return binaryHeapIsMinHeap(bh, left) && binaryHeapIsMinHeap(bh, right);
}

// Deallocate memory for heap
void binaryHeapClear(struct BinaryHeap* bh){
	binaryHeapState(bh);
	free(bh->heap);
	free(bh);
}


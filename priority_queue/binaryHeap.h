/*
 * A min priotity queue implementaion using a binary heap
*/

#include <stdbool.h>

typedef struct BinaryHeap{
	// The number of elements currently inside the heap
	int size;
	// The internal capacity of the heap
	int capacity;
	// Pointer to the array to track the elements inside the heap
	int* heap;
	bool state;
}BinaryHeap;

// Initialize binary heap with max capacity it will activate heap
void binaryHeapInit(struct BinaryHeap* bh, int capacity);

// Check if the current binary heap is active
bool binaryHeapIsActive(struct BinaryHeap* bh);

// Error handling if the binary heap is inactive
void binaryHeapState(struct BinaryHeap* bh);

// Return the size of binary heap.
int binaryHeapSize(struct BinaryHeap* bh);

// Return the capacity of binary heap
int binaryHeapCapacity(struct BinaryHeap* bh);

// Check if the binary heap is empty
bool binaryHeapIsEmpty(struct BinaryHeap* bh);
	
// Helper function swap two element in an array with the given index
void binaryHeapSwap(struct BinaryHeap* bh, int i, int j);

// This function assume i & j are valid indices, O(1) // Helper function
bool binaryHeapLess(struct BinaryHeap* bh, int i, int j);

// Perform bottom up node swim (bubble up), O(log(n))
void binaryHeapSwim(struct BinaryHeap* bh, int k);
	
// Add an element to priority queue
void binaryHeapAdd(struct BinaryHeap* bh, int data);

// Top down node sink(bubble down), O(log(n))
void binaryHeapSink(struct BinaryHeap* bh, int k);

// Remove a node at particular index, O(log(n))
int binaryHeapRemoveAt(struct BinaryHeap* bh, int i);

// Remove a particular element in the heap, O(n)
bool binaryHeapRemove(struct BinaryHeap* bh, int data);

// Remove the root of the heap, O(log(n))
int binaryHeapPoll(struct BinaryHeap* bh);

// Recursively checks if this heap is a min heap
// Called this method with k=0 to start at the root
bool binaryHeapIsMinHeap(struct BinaryHeap* bh, int k);

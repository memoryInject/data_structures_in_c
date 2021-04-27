/*
 * An indexed min priotity queue implementaion using a binary heap
 * To use this implementaion first map all your keys to the integer domain [0, N)
 * where N is the number of keys you have and then use the mapping with this
 * indexed priority queue.
 * 'ki' - key index, ki = map[k]
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdbool.h>

typedef struct IdxBinaryHeap{
	// The number of elements currently inside the heap
	int sz;
	
	// Maximum number of elements in the heap
	int N;

	// The degree of every node in the heap (for binary heap it's 2)
	int D;

	// Lookup arrays to track the child/parent indexes of each node
	int* child;
	int* parent;

	// The Position Map (pm) maps Key Indexes (ki) to where the position of 
	// that key is represented in the priority queue in the domain [0, sz)
	int* pm;

	// The inverse map (im) stores the indexes of the keys in the range [0, sz)
	// which make up the priority queue. It shoud be noted that 'im' and 'pm'
	// are inverse of each other, so: pm[im[i]] = im[pm[i]] = i
	int* im;

	// The values associated with the keys. It is very importent to note that
	// this array is indexed by the key indexes (aka 'ki')
	int* values;

	bool state; // Active/Deactive binary heap

}IdxBinaryHeap;

// Initialize a indexed binary heap with a maximum capacity of maxSize.
struct IdxBinaryHeap* idxBinaryHeapInit(int maxSize);

bool idxBinaryHeapIsActive(struct IdxBinaryHeap* ibh);

// Error handling if the binary heap is inactive
void idxBinaryHeapState(struct IdxBinaryHeap* ibh);

// Return the size of binary heap.
int idxBinaryHeapSize(struct IdxBinaryHeap* ibh);

bool idxBinaryHeapIsEmpty(struct IdxBinaryHeap* ibh);

bool idxBinaryHeapContains(struct IdxBinaryHeap* ibh, int ki);

int idxBinaryHeapPeekMinKeyIndex(struct IdxBinaryHeap* ibh);

int idxBinaryHeapPeekMinValue(struct IdxBinaryHeap* ibh);

// Helper method
void swap(struct IdxBinaryHeap* ibh, int i, int j);

// Helper method: Tests if the value of node i < node j
bool less(struct IdxBinaryHeap* ibh, int i, int j);

// Helper method: From the parent node at index i find the minimum child 
// below it
int minChild(struct IdxBinaryHeap* ibh, int i);

// Helper method sink node down the tree
void sink(struct IdxBinaryHeap* ibh, int i);

// Helper method swim up the node in the tree
void swim(struct IdxBinaryHeap* ibh, int i);

// Helper method to insert key index and value
void insert(struct IdxBinaryHeap* ibh, int ki, int value);

// Helper method delete node based on key index
int deleteKi(struct IdxBinaryHeap* ibh, int ki);

// Helper method update a node's value based on key index
int update(struct IdxBinaryHeap* ibh, int ki, int value);

// Helper method strictly decrease the value associated with 'ki' to 'value'
void decrease(struct IdxBinaryHeap* ibh, int ki, int value);

// Helper method strictly increase the value associated with 'ki' to 'value'
void increase(struct IdxBinaryHeap* ibh, int ki, int value);

// Helper method
bool isMinHeap(struct IdxBinaryHeap* ibh, int i);

int valueOf(struct IdxBinaryHeap* ibh, int ki);

int idxBinaryHeapPollMinKeyIndex(struct IdxBinaryHeap* ibh);

int idxBinaryHeapPollMinValue(struct IdxBinaryHeap* ibh);

void idxBinaryHeapInsert(struct IdxBinaryHeap* ibh, int ki, int value);

int idxBinaryHeapValueOf(struct IdxBinaryHeap* ibh, int ki);

int idxBinaryHeapDelete(struct IdxBinaryHeap* ibh, int ki);

int idxBinaryHeapUpdate(struct IdxBinaryHeap* ibh, int ki, int value);

void idxBinaryHeapDecrease(struct IdxBinaryHeap* ibh, int ki, int value);

void idxBinaryHeapIncrease(struct IdxBinaryHeap* ibh, int ki, int value);

void idxBinaryHeapClear(struct IdxBinaryHeap* ibh);

void idxBinaryHeapPrint(struct IdxBinaryHeap* ibh);

// Print values in the binary heap as tree
void idxBinaryHeapPrintTree(struct IdxBinaryHeap* ibh);


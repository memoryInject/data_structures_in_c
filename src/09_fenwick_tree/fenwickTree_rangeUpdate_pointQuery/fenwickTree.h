/*
 * Fenwick Tree Range update, Point query
 * A Fenwick tree implementation which supports range updates and point queries
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdbool.h>

// Struct for Fenwick Tree
typedef struct FenwickTree{
	// The size of the array holding the fenwick tree values
	int N;

	// This array contains the original Fenwick tree range
	//  values from when it was first created.
	long* originalTree;

	// The current tree will contain the updated range values
	long* currentTree;

	bool state; // Activate/ deactivate tree

}FenwickTree;

// Helper method: lsb - returns the value of the least significant bit (LSB)
// lsb(108) = lsb(0b1101(1)00) = 0b100 = 4
// lsb(104) = lsb(0b1101000) =    0b1000 = 8
// lsb(96)  = lsb(0b1100000) =  0b100000 = 32
// lsb(64)  = lsb(0b1000000) = 0b1000000 = 64
int lsb(int i);

// Construct a Fenwick tree with an initial set of values. The 'values' array
//  MUST BE ONE BASED meaning values[0] doesn't get used, O(n) construction
void fenwickTreeInit(struct FenwickTree* ft, long* values, int length);

// Check if the tree is active
bool fenwickTreeIsActive(struct FenwickTree* ft);

// Error handling if the tree is inactive
void fenwickTreeState(struct FenwickTree* ft);

// Add 'v' to index 'i' and all the ranges responsible for 'i', O(log(n))
void fenwickTreeAdd(struct FenwickTree* ft, int i, long v);

// Update the interval [left, right] with the value 'val', O(log(n))
void fenwickTreeUpdateRange(struct FenwickTree* ft, int left, int right, long val);

// Helper method: Compute prefix sum from [1, i], O(log(n))
long prefixSum(int i, long* tree);

// Get the value at a specific index. The logic behind this method is the
//	same as finding the prefix sum un a Fenwick tree except that you need to
//	take the difference between the current tree and the original to get 
//	the point value.
long fenwickTreeGet(struct FenwickTree* ft, int i);

// Clen up tree
void fenwickTreeClear(struct FenwickTree* ft);

// Print pretty tree data, O(n)
void fenwickTreePrint(struct FenwickTree* ft);


/*
 * Fenwick Tree Range Query, Point Update
 * A Fenwick tree implementation which supports updates and sum range queries
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdbool.h>

// Struct for Fenwick Tree
typedef struct FenwickTree{
	// The size of the array holding the fenwick tree values
	int N;

	// This array contains the Fenwick tree ranges
	long* tree;

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
struct FenwickTree* fenwickTreeInit(long* values, int length);
	
// Check if the tree is active
bool fenwickTreeIsActive(struct FenwickTree* ft);

// Error handling if the tree is inactive
void fenwickTreeState(struct FenwickTree* ft);

// Compute prefix sum from [1, i], O(log(n))
long fenwickTreePrefixSum(struct FenwickTree* ft, int i);

// Return the sum of the interval [left, right], O(long(n))
long fenwickTreeSum(struct FenwickTree* ft, int left, int right);

// Get at index i
long fenwickTreeGet(struct FenwickTree* ft, int i);

// Add 'v' to index 'i', O(log(n))
void fenwickTreeAdd(struct FenwickTree* ft, int i, long v);

// Set index i to be equal to v, O(log(n))
void fenwickTreeSet(struct FenwickTree* ft, int i, long v);

// Clen up tree
void fenwickTreeClear(struct FenwickTree* ft);

// Print pretty tree data, O(n)
void fenwickTreePrint(struct FenwickTree* ft);


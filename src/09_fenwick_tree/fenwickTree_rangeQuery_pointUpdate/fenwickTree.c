/*
 * Fenwick Tree Range Query, Point Update
 * A Fenwick tree implementation which supports updates and sum range queries
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "fenwickTree.h"

// Helper method: lsb - returns the value of the least significant bit (LSB)
// lsb(108) = lsb(0b1101(1)00) = 0b100 = 4
// lsb(104) = lsb(0b1101000) =    0b1000 = 8
// lsb(96)  = lsb(0b1100000) =  0b100000 = 32
// lsb(64)  = lsb(0b1000000) = 0b1000000 = 64
int lsb(int i) {
	// Isolate the lowest one bit value
	return i & -i;
}

// Construct a Fenwick tree with an initial set of values. The 'values' array
//  MUST BE ONE BASED meaning values[0] doesn't get used, O(n) construction
struct FenwickTree* fenwickTreeInit(long* values, int length){
	struct FenwickTree* ft = (struct FenwickTree*) malloc(sizeof(struct FenwickTree));
	ft->N = length;
	values[0] = 0;

	// Construct tree array
	ft->tree = (long*) malloc(sizeof(long) * length);

	// Make clone of value array
	for(int i = 0; i < length; i++){
		ft->tree[i] = values[i];
	}

	// Replace cloned value. We manipulate the array in place destroying all it's
	//  original content
	for(int i = 1; i < length; i++){
		int parent = i + lsb(i);
		if(parent < length) ft->tree[parent] += ft->tree[i];
	}

	ft->state = true; // activate the tree

	return ft;
}

// Check if the tree is active
bool fenwickTreeIsActive(struct FenwickTree* ft){
	return ft->state;
}

// Error handling if the tree is inactive
void fenwickTreeState(struct FenwickTree* ft){
	if(ft->state == false){
		printf("%s, inactive fenwick tree!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Compute prefix sum from [1, i], O(log(n))
long fenwickTreePrefixSum(struct FenwickTree* ft, int i){
	fenwickTreeState(ft);
	long sum = 0;
	while(i != 0){
		sum += ft->tree[i];
		i &= ~lsb(i); // Equivalently, i -= lsb(i);
	}
	return sum;
}

// Return the sum of the interval [left, right], O(long(n))
long fenwickTreeSum(struct FenwickTree* ft, int left, int right){
	fenwickTreeState(ft);
	if(right < left){
		printf("%s, Right must be >= Left!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
	return fenwickTreePrefixSum(ft, right) - fenwickTreePrefixSum(ft, left-1);
}

// Get at index i
long fenwickTreeGet(struct FenwickTree* ft, int i){
	fenwickTreeState(ft);
	return fenwickTreeSum(ft, i, i);
}

// Add 'v' to index 'i', O(log(n))
void fenwickTreeAdd(struct FenwickTree* ft, int i, long v){
	fenwickTreeState(ft);
	while(i < ft->N) {
		ft->tree[i] += v;
		i += lsb(i);
	}
}

// Set index i to be equal to v, O(log(n))
void fenwickTreeSet(struct FenwickTree* ft, int i, long v){
	fenwickTreeState(ft);
	fenwickTreeAdd(ft, i, v - fenwickTreeSum(ft, i, i));
}

// Clen up tree
void fenwickTreeClear(struct FenwickTree* ft){
	fenwickTreeState(ft);
	free(ft->tree);
	ft->N = 0;

	free(ft);
}

// Print pretty tree data, O(n)
void fenwickTreePrint(struct FenwickTree* ft){
	fenwickTreeState(ft);
	for(int i = 1; i < ft->N; i++){
		printf("index: %d	data: %ld\n", i, ft->tree[i]);
	}
}



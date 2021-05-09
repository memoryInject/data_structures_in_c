/*
 * Fenwick Tree Range update, Point query
 * A Fenwick tree implementation which supports range updates and point queries
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
void fenwickTreeInit(struct FenwickTree* ft, long* values, int length){
	ft->N = length;
	values[0] = 0;

	// Construct trees array
	ft->originalTree = (long*) malloc(sizeof(long) * length);
	ft->currentTree = (long*) malloc(sizeof(long) * length);

	// Make clone of value array
	for(int i = 0; i < length; i++){
		ft->originalTree[i] = values[i];
	}

	// Replace cloned value. We manipulate the array in place destroying all it's
	//  original content
	for(int i = 1; i < length; i++){
		int parent = i + lsb(i);
		if(parent < length){
 			ft->originalTree[parent] += ft->originalTree[i];
		}
	}
	
	// Copy original to current
	for (int i = 0; i < length; i++){
		ft->currentTree[i] = ft->originalTree[i];
	}

	ft->state = true; // activate the tree
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

// Add 'v' to index 'i' and all the ranges responsible for 'i', O(log(n))
void fenwickTreeAdd(struct FenwickTree* ft, int i, long v){
	fenwickTreeState(ft);
	while(i < ft->N) {
		ft->currentTree[i] += v;
		i += lsb(i);
	}
}

// Update the interval [left, right] with the value 'val', O(log(n))
void fenwickTreeUpdateRange(struct FenwickTree* ft, int left, int right, long val){
	fenwickTreeState(ft);
	if(right < left){
		printf("%s, Right must be >= Left!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
	fenwickTreeAdd(ft, left, +val);
	fenwickTreeAdd(ft, right + 1, -val);
}

// Helper method: Compute prefix sum from [1, i], O(log(n))
long prefixSum(int i, long* tree){
	long sum = 0;
	while(i != 0){
		sum += tree[i];
		i &= ~lsb(i); // Equivalently, i -= lsb(i);
	}
	return sum;
}

// Get the value at a specific index. The logic behind this method is the
//	same as finding the prefix sum un a Fenwick tree except that you need to
//	take the difference between the current tree and the original to get 
//	the point value.
long fenwickTreeGet(struct FenwickTree* ft, int i){
	fenwickTreeState(ft);
	return prefixSum(i, ft->currentTree) - prefixSum(i - 1, ft->originalTree);
}

// Clen up tree
void fenwickTreeClear(struct FenwickTree* ft){
	fenwickTreeState(ft);
	free(ft->originalTree);
	free(ft->currentTree);
	ft->N = 0;
}

// Print pretty tree data, O(n)
void fenwickTreePrint(struct FenwickTree* ft){
	fenwickTreeState(ft);
	printf("Origianl Tree: \n");
	for(int i = 1; i < ft->N; i++){
		printf("index: %d	data: %ld\n", i, ft->originalTree[i]);
	}

	printf("\nCurrent Tree: \n");
	for(int i = 1; i < ft->N; i++){
		printf("index: %d	data: %ld\n", i, ft->currentTree[i]);
	}
}


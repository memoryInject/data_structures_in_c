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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>

#include "indexedBinaryHeap.h"

// Helper method: find maximum between two numbers
int max(int a, int b){
	return (a > b) ? a : b;
}

// Helper method: find minimum between two numbers
int min(int a, int b){
	return (a < b) ? a : b;
}

// Helper method: math power
int power(int base, int exponent){
	int result = 1;
	for (; exponent > 0; exponent--) result *= base;
	return result;
}

// Initialize a indexed binary heap with a maximum capacity of maxSize.
void idxBinaryHeapInit(struct IdxBinaryHeap* ibh, int maxSize){
	ibh->D = 2; // for binay heap
	ibh->N = max(ibh->D+1, maxSize);
	
	ibh->pm = (int*) malloc(sizeof(int) * ibh->N);
	ibh->im = (int*) malloc(sizeof(int) * ibh->N);
	ibh->child = (int*) malloc(sizeof(int) * ibh->N);
	ibh->parent = (int*) malloc(sizeof(int) * ibh->N);
	ibh->values = (int*) malloc(sizeof(int) * ibh->N);

	for (int i = 0; i < ibh->N; i++){
		ibh->parent[i] = (i - 1) / ibh->D;
		ibh->child[i] = i * ibh->D + 1;
		ibh->pm[i] = ibh->im[i] = -1;
	}

	ibh->sz = 0; // Initial size to 0

	// Activate the heap
	ibh->state = true;
}

bool idxBinaryHeapIsActive(struct IdxBinaryHeap* ibh){
	return ibh->state;
}

// Error handling if the binary heap is inactive
void idxBinaryHeapState(struct IdxBinaryHeap* ibh){
	if(ibh->state == false){
		printf("%s, inactive binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the size of binary heap.
int idxBinaryHeapSize(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	return ibh->sz;
}

bool idxBinaryHeapIsEmpty(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	return ibh->sz == 0;
}

bool idxBinaryHeapContains(struct IdxBinaryHeap* ibh, int ki){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	if(ki > ibh->N){
		printf("%s, index out of binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
	return ibh->pm[ki] != -1;
}

int idxBinaryHeapPeekMinKeyIndex(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	if(idxBinaryHeapIsEmpty(ibh)){
		printf("%s, Empty binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
	return ibh->im[0];
}

int idxBinaryHeapPeekMinValue(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	if(idxBinaryHeapIsEmpty(ibh)){
		printf("%s, Empty binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
	return ibh->values[ibh->im[0]];
}

// Helper method
void swap(struct IdxBinaryHeap* ibh, int i, int j){
	ibh->pm[ibh->im[j]] = i;
	ibh->pm[ibh->im[i]] = j;
	int tmp = ibh->im[i];
	ibh->im[i] = ibh->im[j];
	ibh->im[j] = tmp;
}
	
// Helper method: Tests if the value of node i < node j
bool less(struct IdxBinaryHeap* ibh, int i, int j){
	return ibh->values[ibh->im[i]] < ibh->values[ibh->im[j]];
}

// Helper method: From the parent node at index i find the minimum child 
// below it
int minChild(struct IdxBinaryHeap* ibh, int i){
	int index = -1, from = ibh->child[i], to = min(ibh->sz, from + ibh->D);
	for(int j = from; j < to; j++){
		if (less(ibh, j, i)) index = i = j;
	}
	return index;
}

// Helper method sink node down the tree
void sink(struct IdxBinaryHeap* ibh, int i){
	for (int j = minChild(ibh, i); j != -1;){
		swap(ibh, i, j);	
		i = j;
		j = minChild(ibh, i);
	}
}

// Helper method swim up the node in the tree
void swim(struct IdxBinaryHeap* ibh, int i){
	while(less(ibh, i, ibh->parent[i])){
		swap(ibh, i, ibh->parent[i]);
		i = ibh->parent[i];
	}
}

// Helper method to insert key index and value
void insert(struct IdxBinaryHeap* ibh, int ki, int value){
	if(idxBinaryHeapContains(ibh, ki)){
		printf("%s, key index already in binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}	
	ibh->pm[ki] = ibh->sz;
	ibh->im[ibh->sz] = ki;
	ibh->values[ki] = value;
	swim(ibh, ibh->sz++);
}

// Helper method delete node based on key index
int deleteKi(struct IdxBinaryHeap* ibh, int ki){
	if(!idxBinaryHeapContains(ibh, ki)){
		printf("%s, key index not in binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}	
	int i = ibh->pm[ki];
	swap(ibh, i, --ibh->sz);
	sink(ibh, i);
	swim(ibh, i);
	int value = ibh->values[ki];
	ibh->values[ki] = -1;
	ibh->pm[ki] = -1;
	ibh->im[ibh->sz] = -1;
	return value;
}

// Helper method update a node's value based on key index
int update(struct IdxBinaryHeap* ibh, int ki, int value){
	if(!idxBinaryHeapContains(ibh, ki)){
		printf("%s, key index not in binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}	
	int i = ibh->pm[ki];
	int oldValue = ibh->values[ki];
	ibh->values[ki] = value;
	sink(ibh, i);
	swim(ibh, i);
	return oldValue;
}

// Helper method strictly decrease the value associated with 'ki' to 'value'
void decrease(struct IdxBinaryHeap* ibh, int ki, int value){
	if(!idxBinaryHeapContains(ibh, ki)){
		printf("%s, key index not in binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}	
	if(less(ibh, value, ibh->values[ki])){
		ibh->values[ki] = value;
		swim(ibh, ibh->pm[ki]);
	}	
}

// Helper method strictly increase the value associated with 'ki' to 'value'
void increase(struct IdxBinaryHeap* ibh, int ki, int value){
	if(!idxBinaryHeapContains(ibh, ki)){
		printf("%s, key index not in binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}	
	if(less(ibh, ibh->values[ki], value)){
		ibh->values[ki] = value;
		sink(ibh, ibh->pm[ki]);
	}
}

// Helper method
bool isMinHeap(struct IdxBinaryHeap* ibh, int i){
	int from = ibh->child[i], to = min(ibh->sz, from + ibh->D);
	for (int j = from; j < to; j++){
		if(!less(ibh, i, j)) return false;
		if(!isMinHeap(ibh, j)) return false;
	}
	return true;
}

int valueOf(struct IdxBinaryHeap* ibh, int ki){
	if(!idxBinaryHeapContains(ibh, ki)){
		printf("%s, key index not in binary heap!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}	
	return ibh->values[ki];
}

int idxBinaryHeapPollMinKeyIndex(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	int minki = idxBinaryHeapPeekMinKeyIndex(ibh);
	deleteKi(ibh, minki);
	return minki;
}

int idxBinaryHeapPollMinValue(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	int minValue = idxBinaryHeapPeekMinValue(ibh);
	deleteKi(ibh, idxBinaryHeapPeekMinKeyIndex(ibh));
	return minValue;
}

void idxBinaryHeapInsert(struct IdxBinaryHeap* ibh, int ki, int value){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	insert(ibh, ki, value);	
}

int idxBinaryHeapValueOf(struct IdxBinaryHeap* ibh, int ki){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	return valueOf(ibh, ki);	
}

int idxBinaryHeapDelete(struct IdxBinaryHeap* ibh, int ki){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	return deleteKi(ibh, ki);	
}

int idxBinaryHeapUpdate(struct IdxBinaryHeap* ibh, int ki, int value){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	return update(ibh, ki, value);	
}

void idxBinaryHeapDecrease(struct IdxBinaryHeap* ibh, int ki, int value){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	decrease(ibh, ki, value);	
}

void idxBinaryHeapIncrease(struct IdxBinaryHeap* ibh, int ki, int value){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	increase(ibh, ki, value);	
}

void idxBinaryHeapClear(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	
	ibh->N = 0;	

	free(ibh->pm);
	free(ibh->im);
	free(ibh->child);
	free(ibh->parent);
	free(ibh->values);

	ibh->sz = 0; // Initial size to 0

	// Deactivate the heap
	ibh->state = false;
}

void idxBinaryHeapPrint(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	

	printf("\n");
	// Print key index
	printf("Key index: \n");
	for (int i = 0; i < ibh->sz; i++){
		printf("%d  ", i);	
	}
	printf("\n");
	printf("\n");

	// Print values
	printf("Values: \n");
	for (int i = 0; i < ibh->sz; i++){
		printf("%d  ", ibh->values[i]);	
	}
	
	printf("\n");
	printf("\n");
	// Print position map
	printf("Position map: \n");
	for (int i = 0; i < ibh->sz; i++){
		printf("%d  ", ibh->pm[i]);	
	}
	printf("\n");
	printf("\n");
	
	// Print inverse map
	printf("Inverse map: \n");
	for (int i = 0; i < ibh->sz; i++){
		printf("%d  ", ibh->im[i]);	
	}
	printf("\n");
	printf("\n");
}

// Print values in the binary heap as tree
void idxBinaryHeapPrintTree(struct IdxBinaryHeap* ibh){
	idxBinaryHeapState(ibh); // Check if the binary heap is active	

	int n = ibh->sz;
	int rows = (int)(log(ibh->sz)/log(2)) + 1;
	int* arr = (int*) malloc(sizeof(int) * n); // for getting the values in order

	for (int i = 0; i < n; i++){
		// Adding values to arr, this way we can use the formula 2*i+1 and 2*i+2 for print tree
		arr[i] = ibh->values[ibh->im[i]];
	}

	printf("Values in the binary heap: \n");
	for (int i = 0; i < rows; i++){
		for(int k = n - i; k >= i; k--){
			printf(" ");
		}
		for(int j=0; j < power(2, i) && j + power(2, i) < n + 1; j++){
			printf("%d ", arr[j+(int)power(2, i)-1]); 
		}
		printf("\n");
	}

	// Clean up memory
	free(arr);
	
}


// Quadratic Probing implementation
/*
 * An implementation of a hash-table using open addressing
 *  with quadratic probing as a collision resolution method.
 *
 * <p> In this implementation we are using the following probe function:
 * H(k, x) = h(k) + f(x) mod 2^n
 *
 * <p> Where h(k) is the hash for the given key, f(x) = (x + x^2)/2
 * and n is a natural number. We are using this probing function
 * because it is guaranteed to find an empty cell (i.e it generates
 * all the numbers in the range [0, 2^n] without repetition for
 * the first 2^n numbers).
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>

#include "hashTableOpenAddressingBase.h"

// Given a number this method finds the next 
// power of two above this value.
int nextPowerOfTwo(int v){
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
    v |= v >> 16;
	v++;
	return v;
}

// Given a number this method finds the previous
// power of two below this value
int highestOneBit(int i){
	i |= (i >> 1);
	i |= (i >> 2);
	i |= (i >> 4);
	return i - (i >> 1);
}

// No setup is needed for quadratic probing
void setupProbing(struct HashTable* htoab, struct Key* key){}


int probe(int x){
	// Quadratic probing function (x^2+x)/2
	return ((x * x) + x) >> 1;
}

// Increase the capacity of the hashtable to the
// next power of two
void increaseCapacityPow(int* capacity){
	(*capacity) = nextPowerOfTwo(*capacity);
}

// Adjust the capacity of the hashtable to be a power of two
void adjustCapacity(int* capacity){
	int pow2 = highestOneBit(*capacity);
	if (*capacity == pow2){
		return;
	} 
	increaseCapacityPow(capacity);
}

// End of Quadratic Probing



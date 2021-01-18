// Linear Probing implementation
/*
 * An implementation of a hash-table using open addressing
 *  with linear probing as a collision resolution method.
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>

#include "hashTableOpenAddressingBase.h"

// This is the linear constant used in the liner probing,
//  it can be any positive number. The table capacity will be 
//  adjusted so that the GCD(capacity, LINEAR_CONSTANT) = 1 
//  so that all buckets can be probed. 
#define LINEAR_CONSTANT 17

void setupProbing(struct HashTable* htoab, struct Key* key){}

int probe(int x){
//	printf("Linear Probing...\n");
	return LINEAR_CONSTANT * x;
}

// Adjust the capacity so that the linear constant and the 
//  table capacity are relatively prime.
void adjustCapacity(int* capacity){
	while(gcd(LINEAR_CONSTANT, *capacity) != 1){
		(*capacity)++;
	}
}

// End of Linear Probing



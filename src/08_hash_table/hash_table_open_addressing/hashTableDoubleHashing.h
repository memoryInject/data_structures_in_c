// Double Hashing implementation
/*
 * An implementation of a hash-table using open addressing
 *  with double hashing as a collision resolution method.
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>
#include <stdbool.h>

#include "hashTableOpenAddressingBase.h"

// Helper method to check if the number is a prime
bool isPrime(int n){
	for (int i = 2; i <= n / 2; ++i){
		// Condition for non-prime
		if(n % i == 0){
			return false;
		}
	}
	return true;
}

int hashKeyDouble;

void setupProbing(struct HashTable* htoab, struct Key* key){
	// Cache second hash value.
	hashKeyDouble = normalizeIndex(htoab->capacity, hash2(key->key));

	// Fail safe to avoid infinite loop.
	if(hashKeyDouble == 0) hashKeyDouble = 1;
}

int probe(int x){
//	printf("Double Hashing...\n");
	return x * hashKeyDouble;
}

// Adjust the capacity until it is a prime number.
// Doing this is to help ensure that GCD(hash, capacity) = 1
// when probing so that all the cells can be reached.
void adjustCapacity(int* capacity){
	while(isPrime(*capacity) == false){
		(*capacity)++;
	}
}

// End of Double Hashing



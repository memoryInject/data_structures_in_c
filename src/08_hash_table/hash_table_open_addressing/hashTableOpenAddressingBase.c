// Hash Table Open Addressing
/*
 * Hash Table Open Addressing Base file for hash-tables with open addressing collision 
 	resolution method such as linear probing, quadratic probing and double hashing.
 *
 * key: string , value: integer
 * 
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "hashTableOpenAddressingBase.h"

//djb2 - algorithm for generating hash: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;

	return hash;
}

//sdbm - algorithm for generating hash: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash2(char* str){
	unsigned long hash = 0;
	int c;

	while ((c = *str++))
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}

// Initialize HashTableOAB
struct HashTable* hashTableInit(int capacity, float loadFactor){
	struct HashTable* htoab = (struct HashTable*) malloc(sizeof(HashTable));
	htoab->capacity = capacity > DEFAULT_CAPACITY ? capacity : DEFAULT_CAPACITY;

	if(loadFactor <= 0 || loadFactor > 1){
		htoab->loadFactor = DEFAULT_LOAD_FACTOR;
	} else {
		htoab->loadFactor = loadFactor;
	}
	
	htoab->threshold = (int) (htoab->capacity * htoab->loadFactor);

	htoab->keys = (struct Key*) malloc((sizeof(struct Key)) * htoab->capacity);
	htoab->values = (struct Value*) malloc((sizeof(struct Value)) * htoab->capacity);

	htoab->state = true;
	htoab->modificationCount = 0;
	htoab->usedBuckets = 0;
	htoab->keyCount = 0;
	htoab->resize = 0;

	return htoab;
}

// Helper method to increase the capacity of the hash table.
void increaseCapacity(struct HashTable* htoab){
	htoab->capacity = (2 * htoab->capacity) + 1;
}

// Check if the hash table is active
bool hashTableIsActive(struct HashTable* htoab){
	return htoab->state;
}

// Error handeling if the hash table is inactive
void hashTableState(struct HashTable* htoab){
	if (htoab->state == false)
	{
		printf("%s, inactive hash table!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the number of keys currently inside the hash table
int hashTableSize(struct HashTable* htoab){
	hashTableState(htoab);
	return htoab->keyCount;
}

// Get the capacity of the hash table
int hashTableCapacity(struct HashTable* htoab){
	hashTableState(htoab);
	return htoab->capacity;
}

// Check if the hash table is empty
bool hashTableIsEmpty(struct HashTable* htoab){
	hashTableState(htoab);
	return htoab->keyCount == 0;
}

// Retunrn how many times resize happend in the hash-table
int hashTableResizeAmount(struct HashTable* htoab){
	hashTableState(htoab);
	return htoab->resize;
}

// Helper method: check if the passed key contains TOMBSTONE
bool isTombstone(struct Key* key){
	if(strcmp(key->key, TOMBSTONE) == 0){
		return true;
	}
	return false;
}

// Helper method: error handeling if the key contains TOMBSTONE
void tombstoneError(struct Key* key){
	if (isTombstone(key))
	{
		printf("%s, key contains TOMBSTONE!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}


// Helper method: convert hash value into an index [0 - capacity]
int normalizeIndex(int capacity, unsigned long keyHash)
{
	return keyHash % (unsigned long)capacity;
}

// Helper method: find the greatest common denominator of a and b
int gcd(int a, int b){
	if(b == 0) return a;
	return gcd(b, a% b);
}

// Helper method: double the size of the hash-table
void resizeTable(struct HashTable* htoab){
	int oldLength = htoab->capacity;
	increaseCapacity(htoab);
	adjustCapacity(&htoab->capacity);

	htoab->threshold = (int) (htoab->capacity * htoab->loadFactor);

	struct Key* oldKeyTable = (struct Key*) malloc((sizeof(struct Key)) * htoab->capacity);
	struct Value* oldValueTable = (struct Value*) malloc((sizeof(struct Value)) * htoab->capacity);

	// Perform key table pointer swap
	struct Key* keyTableTmp = htoab->keys;
	htoab->keys = oldKeyTable;
	oldKeyTable = keyTableTmp;

	// Perform value table pointer swap
	struct Value* valueTableTmp = htoab->values;
	htoab->values = oldValueTable;
	oldValueTable = valueTableTmp;

	// Reset the key count and buckets used since we are about to re-insert
	//	all the keys into hash-table
	htoab->keyCount = 0;
	htoab->usedBuckets = 0;

	for(int i = 0; i < oldLength; i++){
		if(oldKeyTable[i].state == true && (strcmp(oldKeyTable[i].key, TOMBSTONE)!=0)){
			insert(htoab, &oldKeyTable[i], &oldValueTable[i]);
		}
	}
	
	// Clean up memory
	free(oldKeyTable);
	free(oldValueTable);

	// Increment the resize 
	htoab->resize++;
}

// Helper method: insert implementation
struct Value insert(struct HashTable* htoab, struct Key* key, struct Value* value){
	if(htoab->usedBuckets >= htoab->threshold){
		resizeTable(htoab);
	}
	
	setupProbing(htoab, key);

	struct Value dummy;
	dummy.value = -1;

	int offset = normalizeIndex(htoab->capacity, hash(key->key));

	for(int i = offset, j = -1, x = 1; ; i = normalizeIndex(htoab->capacity, (unsigned long)(offset + probe(x++)))){
		// The current slot was previously deleted
		if(strcmp(htoab->keys[i].key, TOMBSTONE)==0){
			if(j == -1){
				j = 1;
			}

			// The current cell already contains a key 
		} else if (htoab->keys[i].state == true) {
			// The key we're trying to insert already exists in the table,
			//  so update it's value with the most recent value
			if(strcmp(htoab->keys[i].key, key->key)==0){
				struct Value oldValue = htoab->values[i];
				if (j == -1){
					htoab->values[i].value = value->value;
				} else {
					strcpy(htoab->keys[i].key, TOMBSTONE);
					
					htoab->keys[j].state = true; // activate the key
					strcpy(htoab->keys[j].key, key->key);
					htoab->values[j].value = value->value;
				}
				htoab->modificationCount++;
				return oldValue;
			}

			// Current cell is empty so an insertion/update can occur
		} else {
			// No previously encountered deleted buckets
			if(j == -1) {
				htoab->usedBuckets++;
				htoab->keyCount++;
				htoab->keys[i].state = true; // activate the key
				strcpy(htoab->keys[i].key, key->key);
				htoab->values[i].value = value->value;

				// Previously seen deleted bucket. Insted of inserting
				//  the new element at i where the null element is 
				//  insert it where the deleted token was found
			} else {
				htoab->keyCount++;
				htoab->keys[j].state = true; // activate the key
				strcpy(htoab->keys[j].key, key->key);
				htoab->values[j].value = value->value;
			}

			htoab->modificationCount++;
			return dummy;
		}
	}
}

// Helper method: return true/false on whether a 
//  given key exists within the hash-table
bool hasKey(struct HashTable* htoab, struct Key* key){
	setupProbing(htoab, key);
	int offset = normalizeIndex(htoab->capacity, hash(key->key));

	// Starting at the original hash linearly probe until
	//  we find a spot where our key is or we hit a null 
	//  element in which case our element does not exists.
	for (int i = offset, j = -1, x = 1; ; i = normalizeIndex(htoab->capacity, (unsigned long)(offset + probe(x++)))){
		// Ignore deleted cells, but record where the first index 
		//  of a deleted cell is found to perform lazy relocation later.
		if(strcmp(htoab->keys[i].key, TOMBSTONE) == 0){
			if(j == -1) j = i;

			// we hit a non null key perhaps it's the one
			//  we are looking for
		} else if (htoab->keys[i].state == true){
			// The key we want is in the hash-table!
			if(strcmp(htoab->keys[i].key, key->key) == 0){
				// If j != -1 this means we previously encountered a 
				//  deleted cell. We can perform an optimization by 
				//  swapping the entries in cells i and j so that the next
				//  time we search for this key it will be found faster.
				//  this is called lazy deletion/relocation.
				if(j != -1){
					// Swap the key-value pairs of position i and j.
					strcpy(htoab->keys[j].key, htoab->keys[i].key);
					htoab->values[j].value = htoab->values[i].value;
					strcpy(htoab->keys[i].key, TOMBSTONE);
				}
				return true;
			}
			// Key was not found in the hash-table 😭
		} else {
			return false;
		}
	}
}

// Helper method: get value associated with the input key
//  return a dummy value, if key doen't exists
struct Value get(struct HashTable* htoab, struct Key* key){
	setupProbing(htoab, key);
	int offset = normalizeIndex(htoab->capacity, hash(key->key));

	// Starting at the original hash linearly probe until
	//  we find a spot where our key is or we hit a null 
	//  element in which case our element does not exists.
	for (int i = offset, j = -1, x = 1; ; i = normalizeIndex(htoab->capacity, (unsigned long)(offset + probe(x++)))){
		// Ignore deleted cells, but record where the first index 
		//  of a deleted cell is found to perform lazy relocation later.
		if(strcmp(htoab->keys[i].key, TOMBSTONE) == 0){
			if(j == -1) j = i;

			// we hit a non null key perhaps it's the one
			//  we are looking for
		} else if (htoab->keys[i].state == true){
			// The key we want is in the hash-table!
			if(strcmp(htoab->keys[i].key, key->key) == 0){
				// If j != -1 this means we previously encountered a 
				//  deleted cell. We can perform an optimization by 
				//  swapping the entries in cells i and j so that the next
				//  time we search for this key it will be found faster.
				//  this is called lazy deletion/relocation.
				if(j != -1){
					// Swap the key-value pairs of position i and j.
					strcpy(htoab->keys[j].key, htoab->keys[i].key);
					htoab->values[j].value = htoab->values[i].value;
					strcpy(htoab->keys[i].key, TOMBSTONE);
					
					return htoab->values[j];
				} else {
					return htoab->values[i];
				}
			}
			// Key was not found in the hash-table 😭
		} else {
			struct Value dummy;
			dummy.state = true;
			return dummy;
		}
	}
}

// Remove a key from the map and return the value.
// Return dummy value, if the key does not exists.
struct Value removeKey(struct HashTable* htoab, struct Key* key){
	setupProbing(htoab, key);
	int offset = normalizeIndex(htoab->capacity, hash(key->key));

	// Starting at the original hash linearly probe until
	//  we find a spot where our key is or we hit a null 
	//  element in which case our element does not exists.
	for (int i = offset, x = 1; ; i = normalizeIndex(htoab->capacity, (unsigned long)(offset + probe(x++)))){
		// Ignore deleted cells 
		if(strcmp(htoab->keys[i].key, TOMBSTONE) == 0){
			continue;
		}

		// Key was not found in the hash table
		if (htoab->keys[i].state == false){
			struct Value dummy;
			dummy.state = true;
			return dummy;
		}
		
		// The key we want to remove is in the hash-table!
		if(strcmp(htoab->keys[i].key, key->key) == 0){
			htoab->keyCount--;
			htoab->modificationCount++;
			struct Value oldValue = htoab->values[i];
			strcpy(htoab->keys[i].key, TOMBSTONE);
			return oldValue;
		}

	}

}

// Helper method: return list of keys in the hash-table.
struct Key* keys(struct HashTable* htoab){
	struct Key* keys = (struct Key*) malloc((sizeof(struct Key)) * htoab->keyCount);
	
	for(int i = 0, j = 0; i < htoab->capacity; i++){
		if(htoab->keys[i].state == true && (strcmp(htoab->keys[i].key, TOMBSTONE) != 0)){
			keys[j].state = true;
			strcpy(keys[j].key, htoab->keys[i].key);
			j++;
		}
	}
	return keys;
}

// Helper method: return list of values in the hash-table.
struct Value* values(struct HashTable* htoab){
	struct Value* values = (struct Value*) malloc((sizeof(struct Value)) * htoab->keyCount);
	
	for(int i = 0, j = 0; i < htoab->capacity; i++){
		if(htoab->keys[i].state == true && (strcmp(htoab->keys[i].key, TOMBSTONE) != 0)){
			values[j].value = htoab->values[i].value;
			j++;
		}
	}
	return values;
}

// Helper method to clean up memory
void clear(struct HashTable* htoab){
	// Clean up memory
	free(htoab->keys);
	free(htoab->values);
	htoab->keyCount = 0;
	htoab->usedBuckets = 0;
	htoab->resize = 0;
	htoab->modificationCount++;
}

// Check if the key is in the hash table
bool hashTableHas(struct HashTable* htoab, struct Key* key){
	hashTableState(htoab);
	tombstoneError(key);
	return hasKey(htoab, key);
}

bool hashTableHasKey(struct HashTable* htoab, char* key){
	hashTableState(htoab);
	struct Key keyTmp;

	strcpy(keyTmp.key, key);
	
	tombstoneError(&keyTmp);

	return hasKey(htoab, &keyTmp);
}


// Insert key-value pair into hash table
struct Value hashTableInsert(struct HashTable* htoab, struct Key* key, struct Value* value){
	hashTableState(htoab);
	tombstoneError(key);
	return insert(htoab, key, value);
}

// Put is same as insert except it only accept actual 'key'(string) and 'value'(int).
// Return 'value' (int) 
int hashTablePut(struct HashTable* htoab, char* key, int value){	
	hashTableState(htoab);
	
	struct Key keyTmp;
	struct Value valueTmp;
	
	strcpy(keyTmp.key, key);
	valueTmp.value = value;
	
	tombstoneError(&keyTmp);

	
	return (insert(htoab, &keyTmp, &valueTmp)).value;
}

// Add is same as put
int hashTableAdd(struct HashTable* htoab, char* key, int value){
	return hashTablePut(htoab, key, value);
}

// return struct Value if the key exists
struct Value hashTableGet(struct HashTable* htoab, struct Key* key){
	hashTableState(htoab);
	tombstoneError(key);
	return get(htoab, key);
}

// Return actual 'value' (int) by passing a 'key' (string)
int hashTableGetValue(struct HashTable* htoab, char* key){
	hashTableState(htoab);
	
	struct Key keyTmp;
	
	strcpy(keyTmp.key, key);
	
	tombstoneError(&keyTmp);
	
	return (get(htoab, &keyTmp)).value;
}

// Remove key from the map, return struct Value
struct Value hashTableRemove(struct HashTable *htoab, struct Key* key){
	
	hashTableState(htoab);
	tombstoneError(key);
	return removeKey(htoab, key);
}

// Remove a Key by passing actual 'key' (string), return true if the key exits
bool hashTableRemoveKey(struct HashTable* htoab, char* key){
	hashTableState(htoab);
	
	struct Key keyTmp;
	
	strcpy(keyTmp.key, key);
	
	tombstoneError(&keyTmp);
	
	return (removeKey(htoab, &keyTmp)).state == true ? false : true;
}

// Return list of keys in the hash-table as an array sturct Key 
struct Key* hashTableKeys(struct HashTable* htoab){
	hashTableState(htoab);
	return keys(htoab);
}

// Return list of values in the hash-table as an array sturct Value 
struct Value* hashTableValues(struct HashTable* htoab){
	hashTableState(htoab);
	return values(htoab);
}

// Clean up memory
void hashTableClear(struct HashTable* htoab){
	hashTableState(htoab);
	clear(htoab);	
	free(htoab);
}

// Print pretty: print key-value pairs in the hash table
void hashTablePrint(struct HashTable* htoab){
	hashTableState(htoab);
	if(hashTableIsEmpty(htoab)){
		printf("Empty hash-table!\n");
	} else {
		for(int i = 0; i < htoab->capacity; i++){
			if(htoab->keys[i].state == true && (isTombstone(&(htoab->keys[i])) == false)){
				printf("key: %s, ", htoab->keys[i].key);
				printf("value: %d  | |	", htoab->values[i].value);
				//printf("hash: %ld, ", hash(htoab->keys[i].key));
				printf("bucketIndex: %d\n", i);
			}
		}
	}
}


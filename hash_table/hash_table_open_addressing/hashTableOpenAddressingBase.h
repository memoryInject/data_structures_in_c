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


#include <stdbool.h>

//djb2 - algorithm for generating hash: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str);

//sdbm - algorithm for generating hash: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash2(char* str);

#define DEFAULT_CAPACITY 7
#define DEFAULT_LOAD_FACTOR 0.65f

// Define a 'TOMBSTONE' to indicate the deletion
// of a key-value pair (type must match the key type)
#define TOMBSTONE "#TOMBSTONE#"

// Key stuct to store key
typedef struct Key{
	char key[32];
	bool state; // for activaing the key
}Key;

// Value struct to store value
typedef struct Value{
	int value;
	bool state; // ture for dummy value.
}Value;

// Struct for HashTableOpenAddressingBase - HashTableOAB (htoab)
typedef struct HashTable{
	float loadFactor;
	int capacity;
	int threshold;
	int modificationCount;

	// 'usedBuckets' count the total number of used buckets
	// inside the hash-table (includes cells marked as deleted). 
	// While 'keyCount' tracks the number of unique keys currently inside 
	// the hash table.
	int usedBuckets;
	int keyCount;

	// Counts how many time resize happend
	int resize; 

	// Thsese arrays store key-value pairs
	struct Key* keys;
	struct Value* values;

	bool state; // Activate/deactivate hash rable
}HashTable;

// Initialize HashTableOAB
void hashTableInit(struct HashTable* htoab, int capacity, float loadFactor);
	
// These three helper methods are used to dictate how the probing
//	is actually occur for whatever open addressing schema you are implementing.
// Implimentation of these methods are in appropriate headers
void setupProbing(struct HashTable* htoab, struct Key* key);

int probe(int x);

// Adjust the capacity of the hash table after it's been made larger.
// This is importent to be able to override because the size of the hashtable controlls
//  the functionality of the probing function.
void adjustCapacity(int* capacity);

// Helper method to increase the capacity of the hash table.
void increaseCapacity(struct HashTable* htoab);

// Check if the hash table is active
bool hashTableIsActive(struct HashTable* htoab);

// Error handeling if the hash table is inactive
void hashTableState(struct HashTable* htoab);

// Return the number of keys currently inside the hash table
int hashTableSize(struct HashTable* htoab);

// Get the capacity of the hash table
int hashTableCapacity(struct HashTable* htoab);

// Check if the hash table is empty
bool hashTableIsEmpty(struct HashTable* htoab);

// Retunrn how many times resize happend in the hash-table
int hashTableResizeAmount(struct HashTable* htoab);

// Helper method: check if the passed key contains TOMBSTONE
bool isTombstone(struct Key* key);

// Helper method: error handeling if the key contains TOMBSTONE
void tombstoneError(struct Key* key);

// Helper method: convert hash value into an index [0 - capacity]
int normalizeIndex(int capacity, unsigned long keyHash);

// Helper method: find the greatest common denominator of a and b
int gcd(int a, int b);

// Place a key-value pair into the hash-table. if the key already
//  exists inside the hash-table then the value is updated
struct Value insert(struct HashTable* htoab, struct Key* key, struct Value* value);

// Helper method: double the size of the hash-table
void resizeTable(struct HashTable* htoab);

// Helper method: return true/false on whether a 
//  given key exists within the hash-table
bool hasKey(struct HashTable* htoab, struct Key* key);

// Helper method: get value associated with the input key
//  return a dummy value, if key doen't exists
struct Value get(struct HashTable* htoab, struct Key* key);

// Remove a key from the map and return the value.
// Return dummy value, if the key does not exists.
struct Value removeKey(struct HashTable* htoab, struct Key* key);

// Helper method: return list of keys in the hash-table.
struct Key* keys(struct HashTable* htoab);

// Helper method: return list of values in the hash-table.
struct Value* values(struct HashTable* htoab);
	
// Helper method to clean up memory
void clear(struct HashTable* htoab);
	
// Check if the key is in the hash table
bool hashTableHas(struct HashTable* htoab, struct Key* key);

bool hashTableHasKey(struct HashTable* htoab, char* key);

// Insert key-value pair into hash table
struct Value hashTableInsert(struct HashTable* htoab, struct Key* key, struct Value* value);

// Put is same as insert except it only accept actual 'key'(string) and 'value'(int).
// Return 'value' (int) 
int hashTablePut(struct HashTable* htoab, char* key, int value);

// Add is same as put
int hashTableAdd(struct HashTable* htoab, char* key, int value);
	
// return struct Value if the key exists
struct Value hashTableGet(struct HashTable* htoab, struct Key* key);

// Return actual 'value' (int) by passing a 'key' (string)
int hashTableGetValue(struct HashTable* htoab, char* key);
	
// Remove key from the map, return struct Value
struct Value hashTableRemove(struct HashTable *htoab, struct Key* key);

// Remove a Key by passing actual 'key' (string), return true if the key exits
bool hashTableRemoveKey(struct HashTable* htoab, char* key);

// Return list of keys in the hash-table as an array sturct Key 
struct Key* hashTableKeys(struct HashTable* htoab);

// Return list of values in the hash-table as an array sturct Value 
struct Value* hashTableValues(struct HashTable* htoab);

// Clean up memory
void hashTableClear(struct HashTable* htoab);

// Print pretty: print key-value pairs in the hash table
void hashTablePrint(struct HashTable* htoab);
	

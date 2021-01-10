/*
 * Hash Table Datastructre using seperate chaining with a linked list (for collision handeling)
 * 
 * This implementation based on William Fiset data structures, william.alexandre.fiset@gmail.com
 * 
 * key: string , value: integer
 * 
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdbool.h>

// Create entry, use this entry as a node data for linked list
typedef struct Entry
{
  unsigned long hash;
  char key[16]; // Reserve only for 16 Char
  int value;
} Entry;

//djb2 - algorithm for generating hash: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str);

// initialize Entry with key and value
void entryInit(struct Entry *entry, char *key, int value);

//-----End of Entry struct------------//

// Create linked list (singly) for separare chaining
// Create node
typedef struct Node
{
  struct Entry *data;
  struct Node *next;
} Node;

// Create linked list struct
typedef struct List
{
  struct Node *head;
  int size;
  bool state; // Check for initialized lists
} List;

// Initialize linked list
void listInit(struct List *list);

// Add a node to the beginig of the list - O(1)
void listAdd(struct List *list, struct Entry *data);

// Remove the first value at the head of the list - O(1);
void listRemoveFirst(struct List *list);

// Remove a arbitrary node O(n)
void listRemoveNode(struct List *list, struct Node *node);

// Remove a particular value in the list O(n)
bool listRemoveData(struct List *list, struct Entry *data);

// Cleanup and empty the list
void listClear(struct List *list);

//----------End of Linked List for seperate chaining--------

#define DEFAULT_CAPACITY 3
#define DEFAULT_LOAD_FACTOR 0.75f

// Create Hash Table Separate Chaining - htsc
typedef struct HashTable
{
  float maxLoadFactor;
  int capacity;
  int threshold;
  int size;
  int activeBuckets;  // keep track of active table/lists
  int resize;         // keep track of resizing happend in hash table
  struct List *table; // array of lists
  bool state;         // active/inactive state
} HashTable;

// Init HashTableSeparateChaining
void hashTableInit(struct HashTable *htsc, int capacity, float maxLoadFactor);

// Check if the hash table is active
bool hashTableIsActive(struct HashTable *htsc);

// Error handling if the hash table is inactive
void hashTableState(struct HashTable *htsc);

// Return the number of elements currently inside the hash table
int hashTableSize(struct HashTable *htsc);

// Return active buckets in the hash table
int hashTableActiveBuckets(struct HashTable *htsc);

// Return how many times hash table resized - lower is better
int hashTableResizeAmount(struct HashTable *htsc);

// Check the capacity of the hash table
int hashTableCapacity(struct HashTable *htsc);

// Check if the hash table is empty
int hashTableIsEmpty(struct HashTable *htsc);

// Helper method: convert hash value into an index [0 - capacity]
int normalizeIndex(int capacity, unsigned long keyHash);

// Helper method: find and return a particular Entry
// in a given bucket if it exists, return NULL otherwise.
struct Entry *bucketSeekEntry(struct HashTable *htsc, int bucketIndex, char *key);

// Helper method: resize the internal capacity of hash table for adding more entries
void resizeTable(struct HashTable *htsc);

// Helper method: insert an Entry in a given bucket only if
// the entry already does not exist in the given bucket, but if it does,
// then update the entry value, return the value
int bucketInsertEntry(struct HashTable *htsc, int bucketIndex, struct Entry *entry);

// Helper method: remove an entry from a given bucket if it exists
bool bucketRemoveEntry(struct HashTable *htsc, int bucketIndex, char *key);

// Check if the key is in the hash table
bool hashTableHasKey(struct HashTable *htsc, char *key);

// Insert key-value pair into hash table
int hashTableInsert(struct HashTable *htsc, char *key, int value);

// Put and Add same as insert
int hashTablePut(struct HashTable *htsc, char *key, int value);
int hashTableAdd(struct HashTable *htsc, char *key, int value);

// Get a key's value from the map and return a pointer to value
// return NULL if key does not exist
int *hashTableGet(struct HashTable *htsc, char *key);

// Remove key from the map
bool hashTableRemove(struct HashTable *htsc, char *key);

// Add keys found within the hash table into passed array
void hashTableKeys(struct HashTable *htsc, char **arrKeys);

// Add keys found within the hash table into passed array
void hashTableValues(struct HashTable *htsc, int *arrValues);

// Clean up memory
void hashTableClear(struct HashTable *htsc);

// Print pretty: print key-value pairs in the hash table
void hashTablePrint(struct HashTable *htsc);

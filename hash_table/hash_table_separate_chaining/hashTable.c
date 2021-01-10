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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "hashTable.h"

//djb2 - algorithm for generating hash: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c;

  return hash;
}

// initialize Entry with key and value
void entryInit(struct Entry *entry, char *key, int value)
{
  strcpy(entry->key, key);
  entry->value = value;
  entry->hash = hash(key);
}
//-----End of Entry struct------------//

// Create linked list (singly) for separare chaining
// Initialize linked list
void listInit(struct List *list)
{
  list->head = NULL;
  list->size = 0;
  list->state = true;
}

// Add a node to the beginig of the list - O(1)
void listAdd(struct List *list, struct Entry *data)
{
  // Check if the list is empty
  if (list->size == 0)
  {
    list->head = (struct Node *)malloc(sizeof(struct Node));
    list->head->data = data;
    list->head->next = NULL;
  }
  else
  {
    struct Node *iter = list->head;
    list->head = (struct Node *)malloc(sizeof(struct Node));
    list->head->data = data;
    list->head->next = iter;
  }
  list->size++;
}

// Remove the first value at the head of the list - O(1);
void listRemoveFirst(struct List *list)
{
  struct Node *iter = list->head;
  struct Entry *data = list->head->data;
  list->head = list->head->next;
  --list->size;

  // Clean up memory
  free(data);
  free(iter);
  iter = NULL;
  data = NULL;
}

// Remove a arbitrary node O(n)
void listRemoveNode(struct List *list, struct Node *node)
{

  // Check if the node is removed from the head
  if (node == list->head)
  {
    listRemoveFirst(list);
  }
  else
  {
    // Store the data for clean up
    struct Entry *data = node->data;

    struct Node *iter = list->head;
    while (iter->next != node)
    {
      iter = iter->next;
    }
    // Make the previous node skip over the 'node'
    iter->next = node->next;

    // Clean up memory
    free(data);
    free(node);
    node->next = NULL;
    node = NULL;
    data = NULL;

    // Decrease the list size by one
    --list->size;
  }
}

// Remove a particular value in the list O(n)
bool listRemoveData(struct List *list, struct Entry *data)
{

  struct Node *iter = list->head;
  while (iter != NULL)
  {
    if (iter->data == data)
    {
      listRemoveNode(list, iter);
      return true;
    }
    iter = iter->next;
  }
  return false;
}

// Cleanup and empty the list
void listClear(struct List *list)
{
  struct Node *iter = list->head;
  while (iter != NULL)
  {
    struct Node *next = iter->next;
    free(iter->data); // Clear up Entry, it assigned in malloc from hash table
    iter->data = NULL;
    free(iter);
    iter->next = NULL;
    iter = next;
  }
  list->head = NULL;
  list->size = 0;
  iter = NULL;
}
//----------End of Linked List for seperate chaining--------

// Create Hash Table Separate Chaining - htsc
// Init HashTableSeparateChaining
void hashTableInit(struct HashTable *htsc, int capacity, float maxLoadFactor)
{
  htsc->capacity = capacity > DEFAULT_CAPACITY ? capacity : DEFAULT_CAPACITY;

  if (maxLoadFactor <= 0 || maxLoadFactor > 1)
  {
    htsc->maxLoadFactor = DEFAULT_LOAD_FACTOR;
  }
  else
  {
    htsc->maxLoadFactor = maxLoadFactor;
  }

  htsc->threshold = (int)(htsc->capacity * htsc->maxLoadFactor);
  htsc->table = (struct List *)malloc((sizeof(struct List)) * htsc->capacity);
  htsc->state = true; // activate htsc
  htsc->size = 0;
  htsc->activeBuckets = 0;
  htsc->resize = 0;
}

// Check if the hash table is active
bool hashTableIsActive(struct HashTable *htsc)
{
  return htsc->state;
}

// Error handling if the hash table is inactive
void hashTableState(struct HashTable *htsc)
{
  if (htsc->state == false)
  {
    printf("%s, inactive hash table!!\n", strerror(1));
    exit(EXIT_FAILURE);
  }
}

// Return the number of elements currently inside the hash table
int hashTableSize(struct HashTable *htsc)
{
  hashTableState(htsc);
  return htsc->size;
}

// Return active buckets in the hash table
int hashTableActiveBuckets(struct HashTable *htsc)
{
  hashTableState(htsc);
  return htsc->activeBuckets;
}

// Return how many times hash table resized - lower is better
int hashTableResizeAmount(struct HashTable *htsc)
{
  hashTableState(htsc);
  return htsc->resize;
}

// Check the capacity of the hash table
int hashTableCapacity(struct HashTable *htsc)
{
  hashTableState(htsc);
  return htsc->capacity;
}

// Check if the hash table is empty
int hashTableIsEmpty(struct HashTable *htsc)
{
  hashTableState(htsc);
  return htsc->size == 0;
}

// Helper method: convert hash value into an index [0 - capacity]
int normalizeIndex(int capacity, unsigned long keyHash)
{
  return keyHash % (unsigned long)capacity;
}

// Helper method: find and return a particular Entry in a given bucket if it exists, return null otherwise.
struct Entry *bucketSeekEntry(struct HashTable *htsc, int bucketIndex, char *key)
{
  if (key == NULL)
    return NULL;
  // Get the linked list in the table at bucket index
  struct List *bucket = &(htsc->table[bucketIndex]);
  if (bucket == NULL)
    return NULL;
  // Create a iterator node pointer for traverse list
  struct Node *iter = bucket->head;
  while (iter != NULL)
  {
    // Compare key string
    int i = strcmp(iter->data->key, key);
    // Data stored in the node is an Entry* check if the key is equal
    if (i == 0)
      return iter->data;
    iter = iter->next;
  }
  // Return NULL if the key is not exist
  return NULL;
}

// Helper method: resize the internal capacity of hash table for adding more entries
void resizeTable(struct HashTable *htsc)
{
  int oldCapacity = htsc->capacity;
  htsc->capacity *= 2;
  htsc->threshold = (int)(htsc->capacity * htsc->maxLoadFactor);
  htsc->activeBuckets = 0;
  struct List *newTable = (struct List *)malloc((sizeof(struct List)) * htsc->capacity);
  // Iterate through all the buckets
  for (int i = 0; i < oldCapacity; i++)
  {
    // Check if the table is active
    if (htsc->table[i].state == true)
    {
      struct Node *iter = htsc->table[i].head;
      // Iterate thorugh the list using iter node
      while (iter != NULL)
      {
        // Grab the data from the node
        struct Entry *entry = iter->data;
        // Generate new bucket index based on new capacity
        int bucketIndex = normalizeIndex(htsc->capacity, entry->hash);
        // Garb the list based on the new bucket index
        struct List *bucket = &(newTable[bucketIndex]);
        // Check if the list is not active
        if (bucket->state == false)
        {
          // Initialize new list
          listInit(bucket);
          htsc->activeBuckets++;
        }
        // Add enrty to list
        listAdd(bucket, entry);
        iter = iter->next;
      }
    }
  }
  // Clean up memory from old table
  free(htsc->table);
  // Assign new table with re allocated data with new bucket index
  htsc->table = newTable;
  htsc->resize++; // Increment resize
}

// Helper method: insert an Entry in a given bucket only if
// the entry already does not exist in the given bucket, but if it does,
// then update the entry value, return the value
int bucketInsertEntry(struct HashTable *htsc, int bucketIndex, struct Entry *entry)
{
  struct List *bucket = &(htsc->table[bucketIndex]);
  if (bucket->state == false)
  {
    listInit(bucket);
    htsc->activeBuckets++; // Increment the bucket number
  }
  struct Entry *existEntry = bucketSeekEntry(htsc, bucketIndex, entry->key);
  if (existEntry == NULL)
  {
    listAdd(bucket, entry);
    if (++htsc->size > htsc->threshold)
      resizeTable(htsc);
    return entry->value; // Return new value indicates there was no previous entry
  }
  else
  {
    int oldVal = existEntry->value;
    // Update exist entry with new value
    existEntry->value = entry->value;
    // Return the old value indicate update
    return oldVal;
  }
}

// Helper method: remove an entry from a given bucket if it exists
bool bucketRemoveEntry(struct HashTable *htsc, int bucketIndex, char *key)
{
  struct Entry *entry = bucketSeekEntry(htsc, bucketIndex, key);
  if (entry != NULL)
  {
    struct List *links = &(htsc->table[bucketIndex]);
    listRemoveData(links, entry);
    --htsc->size;
    // Check if the size of list
    if (links->size == 0)
    {
      // Deactivate list
      links->state = false;
      // Decrease the active buckets
      --htsc->activeBuckets;
    }
    return true;
  }
  else
  {
    return false;
  }
}

// Check if the key is in the hash table
bool hashTableHasKey(struct HashTable *htsc, char *key)
{
  hashTableState(htsc);
  int bucketIndex = normalizeIndex(htsc->capacity, hash(key));
  return bucketSeekEntry(htsc, bucketIndex, key) != NULL;
}

// Insert key-value pair into hash table
int hashTableInsert(struct HashTable *htsc, char *key, int value)
{
  hashTableState(htsc);
  struct Entry *entry = (struct Entry *)malloc(sizeof(struct Entry));
  entryInit(entry, key, value);
  int bucketIndex = normalizeIndex(htsc->capacity, entry->hash);
  return bucketInsertEntry(htsc, bucketIndex, entry);
}

// Put and Add same as insert
int hashTablePut(struct HashTable *htsc, char *key, int value)
{
  return hashTableInsert(htsc, key, value);
}

int hashTableAdd(struct HashTable *htsc, char *key, int value)
{
  return hashTableInsert(htsc, key, value);
}

// Get a key's value from the map and return a pointer to value
// return NULL if key does not exist
int *hashTableGet(struct HashTable *htsc, char *key)
{
  hashTableState(htsc);
  int bucketIndex = normalizeIndex(htsc->capacity, hash(key));
  struct Entry *entry = bucketSeekEntry(htsc, bucketIndex, key);
  if (entry != NULL)
  {
    return &(entry->value);
  }
  return NULL;
}

// Remove key from the map
bool hashTableRemove(struct HashTable *htsc, char *key)
{
  hashTableState(htsc);
  int bucketIndex = normalizeIndex(htsc->capacity, hash(key));
  return bucketRemoveEntry(htsc, bucketIndex, key);
}

// Add keys found within the hash table into passed array
void hashTableKeys(struct HashTable *htsc, char **arrKeys)
{
  hashTableState(htsc);
  struct List *bucket;
  int counter = 0;
  for (int i = 0; i < htsc->capacity; i++)
  {
    bucket = &(htsc->table[i]);
    if (bucket != NULL)
    {
      struct Node *iter = bucket->head;
      while (iter != NULL)
      {
        arrKeys[counter] = iter->data->key;
        counter++;
        iter = iter->next;
      }
    }
  }
}

// Add keys found within the hash table into passed array
void hashTableValues(struct HashTable *htsc, int *arrValues)
{
  hashTableState(htsc);
  struct List *bucket;
  int counter = 0;
  for (int i = 0; i < htsc->capacity; i++)
  {
    bucket = &(htsc->table[i]);
    if (bucket != NULL)
    {
      struct Node *iter = bucket->head;
      while (iter != NULL)
      {
        arrValues[counter] = iter->data->value;
        counter++;
        iter = iter->next;
      }
    }
  }
}

// Clean up memory
void hashTableClear(struct HashTable *htsc)
{
  hashTableState(htsc);
  struct List *bucket;
  for (int i = 0; i < htsc->capacity; i++)
  {
    bucket = &(htsc->table[i]);
    if (bucket != NULL)
    {
      listClear(bucket);
    }
  }
  free(htsc->table);
  htsc->size = 0;
}

// Print pretty: print key-value pairs in the hash table
void hashTablePrint(struct HashTable *htsc)
{
  hashTableState(htsc);
  struct List *bucket;
  int counter = 0;
  for (int i = 0; i < htsc->capacity; i++)
  {
    bucket = &(htsc->table[i]);
    if (bucket != NULL)
    {
      struct Node *iter = bucket->head;
      while (iter != NULL)
      {
        char *key = iter->data->key;
        int value = iter->data->value;
        unsigned long hash = iter->data->hash;
        int bucketIndex = normalizeIndex(htsc->capacity, hash);
        counter++;
        iter = iter->next;
        printf("key: %s, value: %d   | |   hash: %ld, bucketIndex: %d\n", key, value, hash, bucketIndex);
      }
    }
  }
}

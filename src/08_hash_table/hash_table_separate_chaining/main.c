#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hashTable.h"

// Test helper methods:
// Generate random string (I got this from stackoverflow)
void randStr(char *dest, size_t length)
{
  char charset[] = "0123456789"
                   "abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  while (length-- > 0)
  {
    size_t index = (double)rand() / RAND_MAX * (sizeof charset - 1);
    *dest++ = charset[index];
  }
  *dest = '\0';
}

// Test driver code for hash table seprarate chain.
int main(int argc, char *argv[])
{
  // Create a hash table - htsc (Hash Table Separate Chaining)
  // Initialize htsc with capacity of 5 and maxLoadFactor of 0.8
  struct HashTable* htsc = hashTableInit(5, 0.6);

  // Add key-value(key: "foo", value: 2) to htsc
  hashTableAdd(htsc, "foo", 2);
  hashTableAdd(htsc, "qHqoDer", 34); // hash value for this key is same as foo

  // Generate random key value pairs and add to hash table
  // Setting up random number
  srand(time(NULL));
  for (int i = 0; i < 10; i++)
  {
    // Generate random string (size 8, max size for key string is 16) for the key
    char str[8];
    randStr(str, sizeof str - 1);

    // Generate random number for value
    int value = (int)((((float)rand() / (float)(RAND_MAX)) * 500) + 100);

    // Add key and value to hash table
    hashTableAdd(htsc, str, value);
  }

  // Check hash table capacity and size
  printf("Capacity: %d, Size: %d\n", hashTableCapacity(htsc), hashTableSize(htsc));

  // Check active buckets in the table
  printf("Active Buckets: %d\n", hashTableActiveBuckets(htsc));

  // Check hash performace
  float perfIndex = ((float)hashTableActiveBuckets(htsc) / (float)hashTableSize(htsc));
  printf("Hash Performace: %s\n", perfIndex > 0.7 ? "Good" : "Fair");

  // Check how many times hash table resized
  printf("Resized: %d times.\n\n", hashTableResizeAmount(htsc));

  // Check if the key exists in the htsc
  printf("Key check: \"foo\", result: %s\n", hashTableHasKey(htsc, "foo") == 1 ? "true" : "false");

  int fooVal = *hashTableGet(htsc, "foo");
  // Get key's value from the table
  printf("\nValue of Key: \"foo\" is, value: %d\n", fooVal);

  // Create a string array to get all the keys from the hash table
  char **arrKeys = (char **)malloc(sizeof(char *) * hashTableSize(htsc));

  // Get all the keys from the hash table
  hashTableKeys(htsc, arrKeys);

  // Print all keys recived from the hash table
  printf("\nKeys Recieved From Hash-Table: \n");
  for (int i = 0; i < hashTableSize(htsc); i++)
  {
    printf("%s\n", arrKeys[i]);
  }

  // Create an int array to get all the values from the hash table
  int *arrValues = (int *)malloc(sizeof(int) * hashTableSize(htsc));

  // Get all the values from the hash table
  hashTableValues(htsc, arrValues);

  // Print all values recived from the hash table
  printf("\nValues Recieved From Hash-Table: \n");
  for (int i = 0; i < hashTableSize(htsc); i++)
  {
    printf("%d\n", arrValues[i]);
  }
  printf("\n");

  // Remove bar from the hash table
  printf("Remove key: \"bar\", result: %s\n", hashTableRemove(htsc, "bar") == 1 ? "true" : "false");

  // Remove qHqoDer from the hash table
  printf("Remove key: \"qHqoDer\", result: %s\n", hashTableRemove(htsc, "qHqoDer") == 1 ? "true" : "false");

  // Remove foo from the hash table
  printf("Remove key: \"foo\", result: %s\n", hashTableRemove(htsc, "foo") == 1 ? "true" : "false");

  printf("Capacity: %d, Size: %d\n", hashTableCapacity(htsc), hashTableSize(htsc));
  printf("Active Buckets: %d\n", hashTableActiveBuckets(htsc));

  // Print all key values in the hash table
  printf("\nPrint Hash Table: \n");
  hashTablePrint(htsc);

  // Clean up memory
  printf("\nClean up memory...\n");
  free(arrKeys);
  free(arrValues);
  hashTableClear(htsc);

  return 0;
}

/*
 * Testing Hash Table Open Addressing with,
 * Linear Probing
 * 
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#include "hashTableLinearProbing.h"


void TestLinearProbing();

// Driver test code
int main(int argc, char* argv[])
{
	// Test for Linear Probing
	TestLinearProbing();

	return 0;
}


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

// Helper method: for key press
void clrKyb(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF){};
}

void pause(){
	printf("Press <ENTER> to continue.");
	clrKyb();
}

// Test Code For Linear Probing
void TestLinearProbing(){
	printf("\nHash Table Open Addressing: Linear Probing - Test Start...\n");
	pause();

	// Create a 'hash table open addressing basic' struct - htoab
	struct HashTable htoab;

	// Initialize hash table with capacity of 5 and loadFactor of 0.7
	hashTableInit(&htoab, 5, 0.7);

	// Add key-value(key: "foo", value: 2) to htoab
	hashTableAdd(&htoab, "foo", 2);

	// Generate random key value pairs and add to hash table
	// Setting up random number
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		// Generate a random num for length of the string
//		int num = (int)((((float)rand() / (float)(RAND_MAX)) * 4) + 4);

		// Generate random string (size 8, max size for key string is 16) for the key
		char str[8];
		randStr(str, sizeof str - 1);

		// Generate random number for value
		int value = (int)((((float)rand() / (float)(RAND_MAX)) * 500) + 100);

		// Add key and value to hash table
		hashTableAdd(&htoab, str, value);
	}

	// Check hash table capacity and size
	printf("Capacity: %d, Size: %d\n", hashTableCapacity(&htoab), hashTableSize(&htoab));

	// Check how many times hash table resized
	printf("Resized: %d times.\n\n", hashTableResizeAmount(&htoab));

	// Check if the key exists in the htoab
	printf("Key check: \"foo\", result: %s\n", hashTableHasKey(&htoab, "foo") == 1 ? "true" : "false");
	
	int fooVal = hashTableGetValue(&htoab, "foo");
	// Get key's value from the table
	printf("\nValue of Key: \"foo\" is, value: %d\n", fooVal);


	// Get all the keys from the hash table
	struct Key* keys = hashTableKeys(&htoab);

	printf("\nKeys Recieved From Hash-Table: \n");
	// Print all keys recived from the hash table
	for (int i = 0; i < hashTableSize(&htoab); i++)
	{
		printf("%s\n", keys[i].key);
	}
	
	free(keys);

	// Get all the values from the hash table
	struct Value* values = hashTableValues(&htoab);

	printf("\nValues Recieved From Hash-Table: \n");
	// Print all values recived from the hash table
	for (int i = 0; i < hashTableSize(&htoab); i++)
	{
		printf("%d\n", values[i].value);
	}
	printf("\n");

	free(values);

	// Remove bar from the hash table
	printf("Remove key: \"bar\", result: %s\n", hashTableRemoveKey(&htoab, "bar") == 1 ? "true" : "false");

	// Remove qHqoDer from the hash table
	printf("Remove key: \"qHqoDer\", result: %s\n", hashTableRemoveKey(&htoab, "qHqoDer") == 1 ? "true" : "false");

	// Remove foo from the hash table
	printf("Remove key: \"foo\", result: %s\n", hashTableRemoveKey(&htoab, "foo") == 1 ? "true" : "false");

	printf("Capacity: %d, Size: %d\n", hashTableCapacity(&htoab), hashTableSize(&htoab));
	
	// Print all key values in the hash table
	printf("\nPrint Hash Table: \n");
	hashTablePrint(&htoab);

	// Clean up memory
	printf("\nClean up memory...\n");
	hashTableClear(&htoab);
	printf("Cleaned up: %s\n", hashTableSize(&htoab) == 0 ? "true" : "false");
	
	printf("%s\n", TOMBSTONE);
	printf("Hash Table Open Addressing: Linear Probing - Test Complete.\n\n");
}


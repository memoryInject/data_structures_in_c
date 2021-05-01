#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../hashTable.h"
#include "../../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

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

void test_function_hashTableSeperateChaining(void){
	// Create a hash table - htsc (Hash Table Separate Chaining)
	// Initialize htsc with capacity of 5 and maxLoadFactor of 0.8
	struct HashTable* htsc = hashTableInit(5, 0.6);

	TEST_ASSERT_EQUAL(hashTableSize(htsc), 0);
	TEST_ASSERT_EQUAL(hashTableIsActive(htsc), true);

	// Add key-value(key: "foo", value: 2) to htsc
	hashTableAdd(htsc, "foo", 2);
	hashTableAdd(htsc, "qHqoDer", 34); // hash value for this key is same as foo

	// Generate random key value pairs and add to hash table
	// Setting up random number
	srand(time(NULL));

	// Create int array to store all the values for testing comparison
	int randNum[12];
	for (int i = 0; i < 10; i++){
		// Generate random string (size 8, max size for key string is 16) for the key
		char str[8];
		randStr(str, sizeof str - 1);

		// Generate random number for value
		int value = (int)((((float)rand() / (float)(RAND_MAX)) * 500) + 100);

		// Add value to rand num array
		randNum[i] = value;

		// Add key and value to hash table
		hashTableAdd(htsc, str, value);
	}

	// Add last entry for "foo"
	randNum[10] = 2;
	randNum[11] = 34;

	TEST_ASSERT_EQUAL(hashTableSize(htsc), 12);
	TEST_ASSERT_EQUAL(hashTableHasKey(htsc, "foo"), true);
	TEST_ASSERT_EQUAL(*hashTableGet(htsc, "foo"), 2);

	// Create an int array to get all the values from the hash table
	int *arrValues = (int *)malloc(sizeof(int) * hashTableSize(htsc));

	// Get all the values from the hash table
	hashTableValues(htsc, arrValues);

	// Check if the values are expected
	int counter = 0;
	for(int i = 0; i < 12; i++){
		for(int j = 0; j < 12; j++){
			if(arrValues[i] == randNum[j]){
				counter++;
			}
		}
	}
	TEST_ASSERT_EQUAL(counter, 12);

	TEST_ASSERT_EQUAL(hashTableRemove(htsc, "bar"), false);
	TEST_ASSERT_EQUAL(hashTableRemove(htsc, "foo"), true);

	// Print all key values in the hash table
	printf("\nPrint Hash Table: \n");
	hashTablePrint(htsc);

	free(arrValues);
	hashTableClear(htsc);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_hashTableSeperateChaining);
	return UNITY_END();
}


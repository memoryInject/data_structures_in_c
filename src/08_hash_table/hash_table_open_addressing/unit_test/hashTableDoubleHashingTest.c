#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../hashTableDoubleHashing.h"
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

void test_function_hashTableDoubleHashing(void){
	// Create a 'hash table open addressing basic' struct - htoab
	// Initialize hash table with capacity of 5 and loadFactor of 0.7
	struct HashTable* htoab = hashTableInit(5, 0.7);

	TEST_ASSERT_EQUAL(hashTableCapacity(htoab) >= 5, true);
	TEST_ASSERT_EQUAL(hashTableSize(htoab), 0);
	TEST_ASSERT_EQUAL(hashTableResizeAmount(htoab), 0);

	// Add key-value(key: "foo", value: 2) to htoab
	hashTableAdd(htoab, "foo", 2);

	TEST_ASSERT_EQUAL(hashTableHasKey(htoab, "foo"), true);

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
		hashTableAdd(htoab, str, value);
	}

	TEST_ASSERT_EQUAL(hashTableSize(htoab), 11);
	TEST_ASSERT_EQUAL(hashTableGetValue(htoab, "foo"), 2); 
	TEST_ASSERT_EQUAL(hashTableRemoveKey(htoab, "bar"), false);
	TEST_ASSERT_EQUAL(hashTableRemoveKey(htoab, "foo"), true);

	
	// Print all key values in the hash table
	printf("\nPrint Hash Table: \n");
	hashTablePrint(htoab);


	hashTableClear(htoab);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_hashTableDoubleHashing);
	return UNITY_END();
}


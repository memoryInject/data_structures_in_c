#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../dynamicArray.h"
#include "../../unit_test_src/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

// Setup dynamic array for test
Array* setupArray(void){
	Array* a = initArray(5); // 5 elements initialized

	int i;
	for(i = 0; i < 10; i++){
		insertArray(a, i);
	}
	return a;
}

void test_function_initArray(void){
	// init 5 elements
	Array* a = initArray(5);
	
	// Check size of the array
	TEST_ASSERT_EQUAL(a->size, 5);

	// Check amount used in array memory
	TEST_ASSERT_EQUAL(a->used, 0);
	freeArray(a);	
}

void test_function_insertArray(void){
	// init 5 elements
	Array* a = initArray(5);

	// Insert an element
	insertArray(a, 2);
	insertArray(a, 4);
	
	// Check size of the array
	TEST_ASSERT_EQUAL(a->size, 5);

	// Check amount used in array memory
	TEST_ASSERT_EQUAL(a->used, 2);

	// Check the element in the array
	TEST_ASSERT_EQUAL(a->array[0], 2);
	TEST_ASSERT_EQUAL(a->array[1], 4);
	
	freeArray(a);	
}

// Test dynamic array auto resize
void test_function_dynamicArray(void){
	Array* a = initArray(5); // 5 elements initialized
	
	// Check size of the array
	TEST_ASSERT_EQUAL(a->size, 5);

	int i;
	for(i = 0; i < 10; i++){
		insertArray(a, i);
	}

	// Check size of the array after adding more elements
	TEST_ASSERT(a->size > 5);

	freeArray(a);	
	
}

// Test popArray
void test_function_popArray(void){

	Array* a = initArray(5); // 5 elements initialized

	int i;
	for(i = 0; i < 10; i++){
		insertArray(a, i);
	}

	// Check used memory in array
	TEST_ASSERT_EQUAL(a->used, 10);

	popArray(a);
	popArray(a);
	
	// Check used memory in array
	TEST_ASSERT_EQUAL(a->used, 8);

	freeArray(a);	
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_initArray);
	RUN_TEST(test_function_insertArray);
	RUN_TEST(test_function_dynamicArray);
	RUN_TEST(test_function_popArray);
	return UNITY_END();
}


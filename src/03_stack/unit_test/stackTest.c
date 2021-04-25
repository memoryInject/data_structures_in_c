#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../stack.h"
#include "../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_stackInit(void){
	
	// Initialize stack
	struct Stack* stack = stackInit();

	TEST_ASSERT_EQUAL(stackIsActive(stack), true);
	TEST_ASSERT_EQUAL(stackSize(stack), 0);
	TEST_ASSERT_EQUAL(stackIsEmpty(stack), true);
	TEST_ASSERT_EQUAL(stack->head, NULL);

	stackPush(stack, 5);

	TEST_ASSERT_EQUAL(stackPeek(stack), 5);

	stackClear(stack);
}

void test_function_stackPush(void){
	
	// Initialize stack
	struct Stack* stack = stackInit();

	// Push elements into the stack
	for(int i = 0; i < 10; i++){
		stackPush(stack, i);
	}

	TEST_ASSERT_EQUAL(stackIsActive(stack), true);
	TEST_ASSERT_EQUAL(stackSize(stack), 10);
	TEST_ASSERT_EQUAL(stackIsEmpty(stack), false);
	TEST_ASSERT_EQUAL(stackPeek(stack), 9);

	stackClear(stack);
}

void test_function_stackPop(void){
	
	// Initialize stack
	struct Stack* stack = stackInit();

	// Push elements into the stack
	for(int i = 0; i < 10; i++){
		stackPush(stack, i);
	}

	TEST_ASSERT_EQUAL(stackIsActive(stack), true);
	TEST_ASSERT_EQUAL(stackSize(stack), 10);
	TEST_ASSERT_EQUAL(stackIsEmpty(stack), false);
	TEST_ASSERT_EQUAL(stackPeek(stack), 9);

	stackPop(stack);
	stackPop(stack);

	TEST_ASSERT_EQUAL(stackSize(stack), 8);
	TEST_ASSERT_EQUAL(stackPeek(stack), 7);

	stackClear(stack);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_stackInit);
	RUN_TEST(test_function_stackInit);
	RUN_TEST(test_function_stackPop);
	return UNITY_END();
}


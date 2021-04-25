#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../queue.h"
#include "../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_queueInit(void){
	
	// Initialize queue 
	struct Queue* queue = queueInit();

	TEST_ASSERT_EQUAL(queueIsActive(queue), true);
	TEST_ASSERT_EQUAL(queueSize(queue), 0);
	TEST_ASSERT_EQUAL(queueIsEmpty(queue), true);
	TEST_ASSERT_EQUAL(queue->head, NULL);

	queuePush(queue, 5);

	TEST_ASSERT_EQUAL(queuePeek(queue), 5);

	queueClear(queue);
}

void test_function_queuePush(void){
	
	// Initialize queue
	struct Queue* queue = queueInit();

	// Push elements into the queue
	for(int i = 0; i < 10; i++){
		queuePush(queue, i);
	}

	TEST_ASSERT_EQUAL(queueIsActive(queue), true);
	TEST_ASSERT_EQUAL(queueSize(queue), 10);
	TEST_ASSERT_EQUAL(queueIsEmpty(queue), false);
	TEST_ASSERT_EQUAL(queuePeek(queue), 0);

	queueClear(queue);
}

void test_function_queuePop(void){
	
	// Initialize queue
	struct Queue* queue = queueInit();

	// Push elements into the queue
	for(int i = 0; i < 10; i++){
		queuePush(queue, i);
	}

	TEST_ASSERT_EQUAL(queueIsActive(queue), true);
	TEST_ASSERT_EQUAL(queueSize(queue), 10);
	TEST_ASSERT_EQUAL(queueIsEmpty(queue), false);
	TEST_ASSERT_EQUAL(queuePeek(queue), 0);

	queuePop(queue);
	queuePop(queue);

	TEST_ASSERT_EQUAL(queueSize(queue), 8);
	TEST_ASSERT_EQUAL(queuePeek(queue), 2);

	queueClear(queue);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_queueInit);
	RUN_TEST(test_function_queuePush);
	RUN_TEST(test_function_queuePop);
	return UNITY_END();
}


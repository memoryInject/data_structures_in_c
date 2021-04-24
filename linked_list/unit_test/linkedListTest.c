#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../linkedList.h"
#include "../../unit_test_src/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_listInit(void){
	//struct List newList;
	struct List* list =	listInit(true);

	TEST_ASSERT_EQUAL(listIsActive(list), true);
	TEST_ASSERT_EQUAL(listSize(list), 0);
	TEST_ASSERT_EQUAL(listIsEmpty(list), true);
	TEST_ASSERT_EQUAL(listIsDoubly(list), true);
	TEST_ASSERT_EQUAL(list->head, NULL);
	TEST_ASSERT_EQUAL(list->tail, NULL);
	listClear(list);
}

void test_function_listAdd(void){

	//struct List newList;
	struct List* list =	listInit(true);

	listAdd(list, 5);
	listAdd(list, 6);
	listAddFirst(list, 3);

	TEST_ASSERT_EQUAL(listPeekFirst(list), 3);
	TEST_ASSERT_EQUAL(listPeekLast(list), 6);
	TEST_ASSERT_EQUAL(listSize(list), 3);

	listClear(list);
}
void test_function_listPop(void){

	//struct List newList;
	struct List* list =	listInit(true);

	listAdd(list, 5);
	listAdd(list, 6);
	listAddFirst(list, 3);

	TEST_ASSERT_EQUAL(listPeekFirst(list), 3);
	TEST_ASSERT_EQUAL(listPeekLast(list), 6);
	TEST_ASSERT_EQUAL(listSize(list), 3);
	TEST_ASSERT_EQUAL(listPop(list), 6);
	TEST_ASSERT_EQUAL(listContains(list, 6), false);

	listClear(list);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_listInit);
	RUN_TEST(test_function_listInit);
	RUN_TEST(test_function_listPop);
	return UNITY_END();
}


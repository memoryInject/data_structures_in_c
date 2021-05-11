#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../suffixArray.h"
#include "../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_suffixArray(void){
	// Text = "banana"
	// suffix array for "banana" {5, 3, 1, 0, 4, 2}
	// least common prefix(lcp) array for "banana" {1, 3, 0, 0, 2, 0}
	char* text = "banana";
	int size = 6;
	struct SuffixArray* sa = suffixArrayInit(text, size);
	suffixArrayPrint(sa);


	TEST_ASSERT_EQUAL(suffixArraySize(sa), size);

	int* saList = suffixArrayGetSA(sa);
	TEST_ASSERT_EQUAL(saList[0], 5);
	TEST_ASSERT_EQUAL(saList[1], 3);
	TEST_ASSERT_EQUAL(saList[2], 1);
	TEST_ASSERT_EQUAL(saList[3], 0);
	TEST_ASSERT_EQUAL(saList[4], 4);
	TEST_ASSERT_EQUAL(saList[5], 2);

	int* lcpList = suffixArrayGetLCP(sa);
	TEST_ASSERT_EQUAL(lcpList[0], 1);
	TEST_ASSERT_EQUAL(lcpList[1], 3);
	TEST_ASSERT_EQUAL(lcpList[2], 0);
	TEST_ASSERT_EQUAL(lcpList[3], 0);
	TEST_ASSERT_EQUAL(lcpList[4], 2);
	TEST_ASSERT_EQUAL(lcpList[5], 0);

	suffixArrayClear(sa);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_suffixArray);
	return UNITY_END();
}


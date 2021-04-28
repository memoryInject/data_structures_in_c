#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../unionFind.h"
#include "../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_unionFind(void){
	// Create UnionFInd
	struct UnionFind* uf = unionFindInit(10);

	TEST_ASSERT_EQUAL(unionFindIsActive(uf), true);
	TEST_ASSERT_EQUAL(unionFindSize(uf), 10);

	// let p=5 and q=6
	int p = 5;
	int q = 6;

	TEST_ASSERT_EQUAL(unionFindFind(uf, p), 5);
	TEST_ASSERT_EQUAL(unionFindFind(uf, q), 6);

	TEST_ASSERT_EQUAL(unionFindConnected(uf, p, q), false);

	unionFindUnify(uf, p, q);
	TEST_ASSERT_EQUAL(unionFindFind(uf, p), 5);
	TEST_ASSERT_EQUAL(unionFindFind(uf, q), 5);

	TEST_ASSERT_EQUAL(unionFindConnected(uf, p, q), true);
	TEST_ASSERT_EQUAL(unionFindComponentSize(uf, p), 2);

	unionFindClear(uf);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_unionFind);
	return UNITY_END();
}


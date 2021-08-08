#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../AVLTree.h"
#include "../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_AVLTree(void){

	// Create a AVL Tree
	struct AVLTree* AVL = avlTreeInit();
	
	// Add data to AVL
	avlTreeAdd(AVL, 12);
	avlTreeAdd(AVL, 2);
	avlTreeAdd(AVL, 14);
	avlTreeAdd(AVL, 5);
	avlTreeAdd(AVL, 1);
	avlTreeAdd(AVL, 3);
	avlTreeAdd(AVL, 8);
	avlTreeAdd(AVL, 23);
	avlTreeAdd(AVL, 24);
	avlTreeAdd(AVL, 16);
	avlTreeAdd(AVL, 18);

	printf("Levelorder traverse: \n");
	avlTreePrintOrder(AVL, LEVEL_ORDER);
	printf("\n");

	printf("Print prettier tree: \n");
	avlTreePrint(AVL);
	printf("\n");

	TEST_ASSERT_EQUAL(AVL->root->data, 14);
	TEST_ASSERT_EQUAL(avlTreeSize(AVL), 11);
	TEST_ASSERT_EQUAL(avlTreeHeight(AVL), 4);
	TEST_ASSERT_EQUAL(avlTreeRemove(AVL, 23), true);


	avlTreeClear(AVL);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_AVLTree);
	return UNITY_END();
}


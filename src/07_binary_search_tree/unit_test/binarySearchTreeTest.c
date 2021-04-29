#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>


#include "../binarySearchTree.h"
#include "../../../libs/unity/unity.h"

// This code run before each test
void setUp(void){

}

// This code run after each test
void tearDown(void){

}

void test_function_binarySearchTree(void){

	// Create a Binary Search Tree
	struct BinarySearchTree* BST = binarySearchTreeInit();
	
	// Add data to BST
	binarySearchTreeAdd(BST, 12);
	binarySearchTreeAdd(BST, 2);
	binarySearchTreeAdd(BST, 14);
	binarySearchTreeAdd(BST, 5);
	binarySearchTreeAdd(BST, 1);
	binarySearchTreeAdd(BST, 3);
	binarySearchTreeAdd(BST, 8);
	binarySearchTreeAdd(BST, 23);
	binarySearchTreeAdd(BST, 24);
	binarySearchTreeAdd(BST, 16);
	binarySearchTreeAdd(BST, 18);

	printf("Levelorder traverse: \n");
	binarySearchTreePrintOrder(BST, LEVEL_ORDER);
	printf("\n");

	printf("Print prettier tree: \n");
	binarySearchTreePrint(BST);
	printf("\n");

	TEST_ASSERT_EQUAL(BST->root->data, 12);
	TEST_ASSERT_EQUAL(binarySearchTreeSize(BST), 11);
	TEST_ASSERT_EQUAL(binarySearchTreeHeight(BST), 4);
	TEST_ASSERT_EQUAL(binarySearchTreeRemove(BST, 23), true);


	binarySearchTreeClear(BST);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_function_binarySearchTree);
	return UNITY_END();
}


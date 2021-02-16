#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "binarySearchTree.h"

// Test driver code
int main(int argc, char* argv[]){
	
	// Setting up random number
	srand(time(NULL));
	int r = rand();
	printf("Random number test: %d\n", (int)(((float)r/(float)(RAND_MAX))*24));

	// Create a Binary Search Tree
	struct BinarySearchTree BST;
	
	// Initialize BST
	binarySearchTreeInit(&BST);
	
	// Add data to BST
	binarySearchTreeAdd(&BST, 12);
	binarySearchTreeAdd(&BST, 2);
	binarySearchTreeAdd(&BST, 14);
	for(int i = 0; i < 24; i++){
		// Add a random number to the tree
		binarySearchTreeAdd(&BST, (int)(((float)r/(float)(RAND_MAX))*i));
	}

	printf("Root data Check: %d\n", BST.root->data);

	// Size of BST
	printf("BST size: %d\n", binarySearchTreeSize(&BST));

	// Traverse BST
	printf("Preorder traverse: \n");
	binarySearchTreePrintOrder(&BST, PRE_ORDER);
	printf("\n");
	
	printf("Inorder traverse: \n");
	binarySearchTreePrintOrder(&BST, IN_ORDER);
	printf("\n");

	printf("Postorder traverse: \n");
	binarySearchTreePrintOrder(&BST, POST_ORDER);
	printf("\n");

	printf("Levelorder traverse: \n");
	binarySearchTreePrintOrder(&BST, LEVEL_ORDER);
	printf("\n");

	printf("Print prettier tree: \n");
	binarySearchTreePrint(&BST);
	printf("\n");

	// BST height
	printf("BST height: %d\n", binarySearchTreeHeight(&BST));
	
	// Remove a node
	int data = 2;
	printf("Remove %d: %s\n", data, binarySearchTreeRemove(&BST, data) == 1 ? "true" : "false");

	// Clean up BST memory
	printf("Clear BST... ");
	binarySearchTreeClear(&BST);
	printf("%s\n", BST.root == NULL ? "Done!" : "Faild!");
	
	return 0;
}

/*
 * AVL Tree test driver program
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "AVLTree.h"

// Test driver code
int main(int argc, char* argv[]){
	// Setting up random number
	srand(time(NULL));
	int r = rand();
	printf("Random number test: %d\n", (int)(((float)r/(float)(RAND_MAX))*24));

	// Create a Binary Search Tree
	struct AVLTree AVL;
	
	// Initialize AVL
	avlTreeInit(&AVL);
	
	// Add data to AVL
	avlTreeAdd(&AVL, 12);
	avlTreeAdd(&AVL, 2);
	avlTreeAdd(&AVL, 14);
	for(int i = 0; i < 24; i++){
		//avlTreeAdd(&AVL, i);
		// Add a random number to the tree
		avlTreeAdd(&AVL, (int)(((float)r/(float)(RAND_MAX))*(i)));
	}

	printf("Root data Check: %d\n", AVL.root->data);

	// Size of AVL
	printf("AVL size: %d\n", avlTreeSize(&AVL));

	// Traverse AVL
	printf("Preorder traverse: \n");
	avlTreePrintOrder(&AVL, PRE_ORDER);
	printf("\n");
	
	printf("Inorder traverse: \n");
	avlTreePrintOrder(&AVL, IN_ORDER);
	printf("\n");

	printf("Postorder traverse: \n");
	avlTreePrintOrder(&AVL, POST_ORDER);
	printf("\n");

	printf("Levelorder traverse: \n");
	avlTreePrintOrder(&AVL, LEVEL_ORDER);
	printf("\n");
	
	printf("Print pretty: \n");
	avlTreePrint(&AVL);
	printf("\n");

	// AVL height
	printf("AVL height: %d\n", avlTreeHeight(&AVL));
	
	// Remove a node
	int data = 2;
	printf("Remove %d: %s\n", data, avlTreeRemove(&AVL, data) == 1 ? "true" : "false");

	// Clean up AVL memory
	printf("Clear AVL... ");
	avlTreeClear(&AVL);
	printf("%s\n", AVL.root == NULL ? "Done!" : "Faild!");
	
	return 0;
}


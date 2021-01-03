/*
 * Binary Search Tree (BST) implementaion.
 * For Level order traverse we use queue data structure.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "binarySearchTree.h"

/*
	 * Queue data structure for implementing level order traversal in BST
*/

// Initialize queue
void queueInit(struct Queue* queue){
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
}

// Push an element to the queue, O(1).
void queuePush(struct Queue* queue, struct Node* treeNode){
	if(queue->size == 0){
		// Allocate memory for head node.
		queue->head = (struct QueueNode*) malloc(sizeof(struct QueueNode));
		queue->head->treeNode = treeNode;
		queue->head->next = NULL;
		queue->tail = queue->head;
		queue->tail->next = NULL;
	}
	else{
		// Iterator for track current tail
		struct QueueNode* iter = queue->tail;
		// Allocate memory for tail node.
		queue->tail = (struct QueueNode*) malloc(sizeof(struct QueueNode));
		queue->tail->treeNode = treeNode;
		queue->tail->next = NULL;
		iter->next = queue->tail;
	}
	// Increment size
	queue->size++;
}

// Pop an element off the queue, O(1).
struct Node* queuePop(struct Queue* queue){
	if(queue->size > 0){
		// Store the data for return in the end.
		struct Node* treeNode = queue->head->treeNode;
		// Store the original head for memory clean up.
		struct QueueNode* iter = queue->head;
		queue->head = queue->head->next;
		free(iter);
		iter = NULL;
		--queue->size;
		return treeNode;
	} else {
		return NULL;
	}
}

// Clear all queue, O(n).
void queueClear(struct Queue* queue){
	// Iterator for travese the queue
	struct QueueNode* iter;
	while(queue->head){
		iter = queue->head;
		queue->head = queue->head->next;
		// Free up the memory used by node
		free(iter);
		iter = NULL;
	}
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
}

/*
	* End of Queue implimentation
*/



// Debug
void debugData(struct Node* node){
	printf("Debug Data: %d\n", node->data);
}

// Initialize BST
void binarySearchTreeInit(struct BinarySearchTree* BST){
	BST->root = NULL;
	BST->nodeCount = 0;
	BST->state = true; // Activate the BST
}

// Check if the BST is active
bool binarySearchTreeIsActive(struct BinarySearchTree* BST){
	return BST->state;
}

// Error handling if the BST is inactive
void binarySearchTreeState(struct BinarySearchTree* BST){
	if(BST->state == false){
		printf("%s, inactive binary search tree!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the size of BST.
int binarySearchTreeSize(struct BinarySearchTree* BST){
	binarySearchTreeState(BST); // Check if the BST is active	
	return BST->nodeCount;
}

// Check if the BST is empty
bool binarySearchTreeIsEmpty(struct BinarySearchTree* BST){
	binarySearchTreeState(BST);
	if(BST->nodeCount == 0){
		return true;
	}
	else{
		return false;
	}
}

// Helper function compare data
int compareData(int a, int b){
	if (a == b){
		return 0;
	} else if (a < b){
		return -1;
	} else {
		return 1;
	}
}

// Helper recursive function to check if the data is in the tree
bool containsData(struct Node* node, int data){
	// Base case: reached the bottom, value not found
	if (node == NULL) return false;
	
	int cmp = compareData(data, node->data);

	if (cmp < 0){
		return containsData(node->left, data);
	} else if (cmp > 0){
		return containsData(node->right, data);
	} else {
		return true;
	}
}

// Helper function add a new node to BST - recursive function
struct Node* addNodeToTree(struct Node* node, int data){
	// Base case: found a leaf node
	if (node == NULL){
		node = (struct Node*)(malloc(sizeof (struct Node)));
		node->data = data;
		node->left = NULL;
		node->right = NULL;
	} else {
		// Pick a subtree to insert data
		if(compareData(data, node->data) < 0){
			node->left = addNodeToTree(node->left, data);
		} else {
			node->right = addNodeToTree(node->right, data);
		}
	}
	return node;
} 

// Helper method to find the leftmost node (which has the smallest value)
struct Node* findMinNode(struct Node* node){
	while(node->left != NULL){
		node = node->left;
	}
	return node;
}

// Helper method to find the rightmost node (which has the largest value)
struct Node* findMaxNode(struct Node* node){
	while(node->right!= NULL){
		node = node->right;
	}
	return node;
}

// Helper method to remove a node from a tree - recursive 
struct Node* removeNode(struct Node* node, int data){
	// Base case
	if(node == NULL) return NULL;

	int cmp = compareData(data, node->data);
	
	// Dig into left subtree, the value we are 
	//  looking for is smaller than the current value.
	if (cmp < 0){
		node->left = removeNode(node->left, data);
		
		// Dig into right subtree, the value we are 
		//  looking for is larger than the current value
	} else if (cmp > 0) {
		node->right = removeNode(node->right, data);

		// Found the node we wish to remove
	} else {
		// This is the case with only a right subtree
		//  or no subtree at all, in this case just
		//	swap the node we wish to remove with it's right child
		if(node->left == NULL){
			struct Node* rightChild = node->right;
			node->data = 0;
			free(node);
			node = NULL;
			return rightChild;

			// In this case with only a left subtree or no subtree at all,
			//  in this case just swap the node with its left child.
		} else if (node->right == NULL){
			struct Node* leftChild = node->left;
			node->data = 0;
			free(node);
			node = NULL;
			return leftChild;

			// When removing a node from a BST with two links the successor 
			//  of the node being removed can either be the largest value in
			//  the left subtree or smallest value in the right subtree.
			//	In this implementation we use smallest value in the right subtree,
			// 	which can be found by traversing as far left as possible in the
			//	right subtree.
		} else {
			// Find the leftmost node in the right subtree.
			struct Node* tmp = findMinNode(node->right);

			// Swap the data
			node->data = tmp->data;

			// Go to the right subtree and remove the left most node
			//	we found and swap the data with. this prevent us having two nodes 
			//	in the tree with the same value.
			node->right = removeNode(node->right, tmp->data);

			// If instead we wanted to find the largest value 
			//	in the left subtree as opposed to smallest value
			//	in the right subtree:
			//struct Node* tmp = findMaxNode(node->left);
			//node->data = tmp->data;
			//node->left = removeNode(node->left, tmp->data);
		}
	}
	return node;
}

// Preorder helper method print data before the recursive call
struct Node* preorderNode(struct Node* node){
	// Base case
	if (node == NULL) return node;
	printf("%d\n", node->data);
	preorderNode(node->left);
	preorderNode(node->right);
	return node;
}

// Inorder helper method print data between the recursive calls
// In BST this print data in increasing order
struct Node* inorderNode(struct Node* node){
	if (node == NULL) return node;
	inorderNode(node->left);
	printf("%d\n", node->data);
	inorderNode(node->right);
	return node;
}

// Postorder helper method print data after the recursive calls
struct Node* postorderNode(struct Node* node){
	if(node == NULL) return node;
	postorderNode(node->left);
	postorderNode(node->right);
	printf("%d\n", node->data);
	return node;
}

// Level order traverse helper method using queue
void levelorderNode(struct Node* node, int size){
	// Bring queue data structure
	struct Queue queue;
	// Initialize queue
	queueInit(&queue);
	// Add the node to queue
	queuePush(&queue, node);
	// Iterator
	struct Node* iter;
	for (int i = 0; i < size; i++){
		// dequeue data from queue, this will return the tree node
		iter = queuePop(&queue);
		printf("%d\n", iter->data);
		// Check if there is any childern, 
		// add children to queue
		if(iter->left != NULL){
			queuePush(&queue, iter->left);
		}
		if(iter->right != NULL){
			queuePush(&queue, iter->right);
		}
	}

	// Clean up queue memory
	queueClear(&queue);
}

// Recursive helper method to compute the hight of the tree
int treeHeight(struct Node* node){
	if (node == NULL) return 0;
	return (treeHeight(node->left) > treeHeight(node->left) ? treeHeight(node->left) : treeHeight(node->right)) + 1;
}

// Clear BST - memory deallocate using postorder traverse recursion
struct Node* clearNode(struct Node* node){
	if(node == NULL) return node;
	clearNode(node->left);
	clearNode(node->right);
	node->data = 0;
	free(node); // Deallocate memory
	node = NULL;
	return node;
}

// Check if the data exists in BST
bool binarySearchTreeContains(struct BinarySearchTree* BST, int data){
	binarySearchTreeState(BST); // Check if the BST is active	
	return containsData(BST->root, data);
}

// Add element to the BST
bool binarySearchTreeAdd(struct BinarySearchTree* BST, int data){
	binarySearchTreeState(BST); // Check if the BST is active	
	// Check if the data already in BST
	if (binarySearchTreeContains(BST, data)){
		return false;
		
	  // Otherwise add this data to BST
	} else {
		BST->root = addNodeToTree(BST->root, data);
		BST->nodeCount++;
		return true;
	}
}

// Remove a node from BST
bool binarySearchTreeRemove(struct BinarySearchTree* BST, int data){
	binarySearchTreeState(BST); // Check if the BST is active	
	// Check if the node exists
	if(binarySearchTreeContains(BST, data)){
		BST->root = removeNode(BST->root, data);
		--BST->nodeCount;
		return true;
	}
	return false;
}

// Travese BST and print data
void binarySearchTreePrint(struct BinarySearchTree* BST, enum traverseOrder order){
	binarySearchTreeState(BST); // Check if the BST is active	
	switch (order){
		case PRE_ORDER:
			BST->root = preorderNode(BST->root);
			break;
		case IN_ORDER:
			BST->root = inorderNode(BST->root);
			break;
		case POST_ORDER:
			BST->root = postorderNode(BST->root);
			break;
		case LEVEL_ORDER:
			levelorderNode(BST->root, BST->nodeCount);
		default:
			break;
	}
}

// Calculate height of the BST
int binarySearchTreeHeight(struct BinarySearchTree* BST){
	return treeHeight(BST->root);
}

// Clean up BST - deallocate node memory
void binarySearchTreeClear(struct BinarySearchTree* BST){
	binarySearchTreeState(BST); // Check if the BST is active	
	BST->root = clearNode(BST->root);
	BST->nodeCount = 0;
}

/*
 * AVL Tree, recursive implementaion.
 * AVL Trees are Binary Search Trees which balances itself
 * to keep operations logarithmic.
 * For Level order traverse we use queue data structure.
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "AVLTree.h"


/*
	 * Queue data structure for implementing level order traversal in AVL Tree
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

// Initialize AVL 
void avlTreeInit(struct AVLTree* AVL){
	AVL->root = NULL;
	AVL->nodeCount = 0;
	AVL->state = true; // Activate the AVL 
}

// Check if the AVL is active
bool avlTreeIsActive(struct AVLTree* AVL){
	return AVL->state;
}

// Error handling if the AVL is inactive
void avlTreeState(struct AVLTree* AVL){
	if(AVL->state == false){
		printf("%s, inactive AVL Tree!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the size of AVL.
int avlTreeSize(struct AVLTree* AVL){
	avlTreeState(AVL); // Check if the AVL Tree is active	
	return AVL->nodeCount;
}

// Check if the AVL is empty
bool avlTreeIsEmpty(struct AVLTree* AVL){
	avlTreeState(AVL);
	if(AVL->nodeCount == 0){
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
	
	// Compare current value to the value in the node
	int cmp = compareData(data, node->data);

	// If cmp < 0 then dig into left subtree, else dig right subtree
	if (cmp < 0){
		return containsData(node->left, data);
	} else if (cmp > 0){
		return containsData(node->right, data);
	} else {
		return true;
	}
}

// Helper method: find maximum between two numbers
int max(int a, int b){
	return (a > b) ? a : b;
}


// Helper function: Update a node's height and balance factor
void update(struct Node* node){
	int leftNodeHeight = (node->left == NULL) ? -1 : node->left->height;
	int rightNodeHeight = (node->right == NULL) ? -1 : node->right->height;

	// Update this node's heght
	node->height = 1 + max(leftNodeHeight, rightNodeHeight); 

	// Update balance factor
	node->bf = rightNodeHeight - leftNodeHeight;
}

// Helper methods for balance the tree

struct Node* leftRotation(struct Node* node){
	struct Node* newParent = node->right;
	node->right = newParent->left;
	newParent->left = node;
	update(node);
	update(newParent);
	return newParent;
}

struct Node* rightRotation(struct Node* node){
	struct Node* newParent = node->left;
	node->left = newParent->right;
	newParent->right = node;
	update(node);
	update(newParent);
	return newParent;
}

struct Node* leftLeftCase(struct Node* node){
	return rightRotation(node);
}

struct Node* leftRightCase(struct Node* node){
	node->left = leftRotation(node->left);
	return leftLeftCase(node);
}

struct Node* rightRightCase(struct Node* node){
	return leftRotation(node);
}

struct Node* rightLeftCase(struct Node* node){
	node->right = rightRotation(node->right);
	return rightRightCase(node);
}

// Re-balance a node if its balance factor is +2 or -2
struct Node* balance(struct Node* node){
	// Left heavy subtree
	if(node->bf == -2){
		// Left-Left case
		if(node->left->bf <= 0){
			return leftLeftCase(node);

			// Left-Right case
		} else {
			return leftRightCase(node);
		}

		// Right heavy subtree needs balancing	
	} else if (node->bf == +2){
		// Right-Right case
		if(node->right->bf >= 0){
			return rightRightCase(node);

			// Right-Left case
		} else {
			return rightLeftCase(node);
		}
	}

	// Node either has a balance factor of 0, +1, -1 which is fine
	return node;
}


// Helper function add a new node to AVL - recursive function
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
			// Insert node in left subtree
			node->left = addNodeToTree(node->left, data);
		} else {
			// Insert node in right subtree
			node->right = addNodeToTree(node->right, data);
		}
	}
	
	// Update balance factor and height values.
	update(node);

	// Re-balance tree.
	return balance(node);
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

			// When removing a node from a AVL with two links the successor 
			//  of the node being removed can either be the largest value in
			//  the left subtree or smallest value in the right subtree.
			//	In this implementation we use smallest value in the right subtree,
			// 	which can be found by traversing as far left as possible in the
			//	right subtree.
		} else {
			// Choose to remove from left subtree
			if(node->left->height > node->right->height){
				// Swap the value of the successor into the node
				struct Node* successorNode = findMaxNode(node->left);
				node->data = successorNode->data;

				// Find the largest node in the left subtree
				node->left = removeNode(node->left, successorNode->data);
				
			} else {
				// Swap the value of the successor value into the node	
				struct Node* successorNode = findMinNode(node->right);
				node->data = successorNode->data;

				// Go to the right subtree and remove the left most node
				//	we found and swap the data with. this prevent 
				//	us having two nodes in the tree with the same value.
				node->right = removeNode(node->right, successorNode->data);
			}
		}
	}
	
	// Update balance factor and height values
	update(node);

	// Re-balance tree
	return balance(node);
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
// In AVL this print data in increasing order
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

// Print prettier tree
int printPretty(Node* node, int isLeft, int offset, int depth, char s[20][255]){
	char b[20];
	int width = 5;

	if (!node)
		return 0;

	sprintf(b, "(%03d)", node->data);

	int left = printPretty(node->left, 1, offset, depth + 1, s);
	int right = printPretty(node->right, 0, offset + left + width, depth + 1, s);

	for (int i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];

	if (depth && isLeft){
		for(int i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';
	} else if (depth && !isLeft){
		for (int i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';

		s[depth - 1][offset + left + width / 2] = '.';
	}

	return left + width + right;
}

// Recursive helper method to compute the hight of the tree
int treeHeight(struct Node* node){
	if (node == NULL) return 0;
	return (treeHeight(node->left) > treeHeight(node->left) ? treeHeight(node->left) : treeHeight(node->right)) + 1;
}

// Clear AVL - memory deallocate using postorder traverse recursion
struct Node* clearNode(struct Node* node){
	if(node == NULL) return node;
	clearNode(node->left);
	clearNode(node->right);
	node->data = 0;
	free(node); // Deallocate memory
	node = NULL;
	return node;
}

// Check if the data exists in AVL Tree
bool avlTreeContains(struct AVLTree* AVL, int data){
	avlTreeState(AVL); // Check if it is active	
	return containsData(AVL->root, data);
}

// Add element to the AVL Tree
bool avlTreeAdd(struct AVLTree* AVL, int data){
	avlTreeState(AVL); // Check if the AVL is active	
	// Check if the data already in AVL
	if (avlTreeContains(AVL, data)){
		return false;
		
	  // Otherwise add this data to AVL
	} else {
		AVL->root = addNodeToTree(AVL->root, data);
		AVL->nodeCount++;
		return true;
	}
}

// Remove a node from AVL
bool avlTreeRemove(struct AVLTree* AVL, int data){
	avlTreeState(AVL); // Check if the AVL is active	
	// Check if the node exists
	if(avlTreeContains(AVL, data)){
		AVL->root = removeNode(AVL->root, data);
		--AVL->nodeCount;
		return true;
	}
	return false;
}

// Travese AVL and print data
void avlTreePrintOrder(struct AVLTree* AVL, enum traverseOrder order){
	avlTreeState(AVL); // Check if the AVL is active	
	switch (order){
		case PRE_ORDER:
			AVL->root = preorderNode(AVL->root);
			break;
		case IN_ORDER:
			AVL->root = inorderNode(AVL->root);
			break;
		case POST_ORDER:
			AVL->root = postorderNode(AVL->root);
			break;
		case LEVEL_ORDER:
			levelorderNode(AVL->root, AVL->nodeCount);
		default:
			break;
	}
}

// Print prettier AVL tree
void avlTreePrint(struct AVLTree* AVL){
	avlTreeState(AVL);
	
	char s[20][255];
	for (int i = 0; i < AVL->root->height; i++)
		sprintf(s[i], "%80s", " ");
	
	printPretty(AVL->root, 0, 0, 0, s);

	for (int i = 0; i <  AVL->root->height; i++)
		printf("%s\n", s[i]);
}

// Calculate height of the AVL
int avlTreeHeight(struct AVLTree* AVL){
	return treeHeight(AVL->root);
}

// Clean up AVL - deallocate node memory
void avlTreeClear(struct AVLTree* AVL){
	avlTreeState(AVL); // Check if the AVL is active	
	AVL->root = clearNode(AVL->root);
	AVL->nodeCount = 0;
}


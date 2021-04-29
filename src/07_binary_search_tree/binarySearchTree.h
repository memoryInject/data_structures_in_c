/*
 * Binary Search Tree (BST) implementaion.
 * For Level order traverse we use queue data structure.
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdbool.h>

// Helper enum for traverse data in a tree
enum traverseOrder {PRE_ORDER, IN_ORDER, POST_ORDER, LEVEL_ORDER};

// Create Node.
typedef struct Node{
	int data;
	struct Node* left;
	struct Node* right; 
}Node;

// Create BST struct, it will hold the root and node counts
typedef struct BinarySearchTree{
	struct Node* root;
	int nodeCount;
	bool state; // check if the list is initialized/active or not
}BinarySearchTree;



/*
	 * Queue data structure for implementing level order traversal in BST
	 ====================================================================
*/

// Create QueueNode for Queue.
typedef struct QueueNode{
	struct Node* treeNode;
	struct QueueNode* next;
}QueueNode;

// Create queue struct to keep track of head, tail, size and state of queue.
typedef struct Queue{
	struct QueueNode* head;
	struct QueueNode* tail;
	int size;
}Queue;

// Initialize queue
struct Queue* queueInit(void);

// Push an element to the queue, O(1).
void queuePush(struct Queue* queue, struct Node* treeNode);

// Pop an element off the queue, O(1).
struct Node* queuePop(struct Queue* queue);

// Clear all queue, O(n).
void queueClear(struct Queue* queue);

/*
	* End of Queue implimentation
	=============================
*/

// Debug
void debugData(struct Node* node);

// Initialize BST
struct BinarySearchTree* binarySearchTreeInit(void);

// Check if the BST is active
bool binarySearchTreeIsActive(struct BinarySearchTree* BST);

// Error handling if the BST is inactive
void binarySearchTreeState(struct BinarySearchTree* BST);

// Return the size of BST.
int binarySearchTreeSize(struct BinarySearchTree* BST);

// Check if the BST is empty
bool binarySearchTreeIsEmpty(struct BinarySearchTree* BST);

// Helper function compare data
int compareData(int a, int b);

// Helper recursive function to check if the data is in the tree
bool containsData(struct Node* node, int data);

// Helper function add a new node to BST - recursive function
struct Node* addNodeToTree(struct Node* node, int data);

// Helper method to find the leftmost node (which has the smallest value)
struct Node* findMinNode(struct Node* node);

// Helper method to find the rightmost node (which has the largest value)
struct Node* findMaxNode(struct Node* node);

// Helper method to remove a node from a tree - recursive 
struct Node* removeNode(struct Node* node, int data);

// Preorder helper method print data before the recursive call
struct Node* preorderNode(struct Node* node);

// Inorder helper method print data between the recursive calls
// In BST this print data in increasing order
struct Node* inorderNode(struct Node* node);

// Postorder helper method print data after the recursive calls
struct Node* postorderNode(struct Node* node);

// Level order traverse helper method using queue
void levelorderNode(struct Node* node, int size);

// Print prettier tree
int printPretty(struct Node* node, int isLeft, int offset, int depth, char s[20][255]);

// Recursive helper method to compute the hight of the tree
int treeHeight(struct Node* node);

// Clear BST - memory deallocate using postorder traverse recursion
struct Node* clearNode(struct Node* node);

// Check if the data exists in BST
bool binarySearchTreeContains(struct BinarySearchTree* BST, int data);

// Add element to the BST
bool binarySearchTreeAdd(struct BinarySearchTree* BST, int data);

// Remove a node from BST
bool binarySearchTreeRemove(struct BinarySearchTree* BST, int data);

// Travese BST and print data
void binarySearchTreePrintOrder(struct BinarySearchTree* BST, enum traverseOrder order);

// Print prettier BST 
void binarySearchTreePrint(struct BinarySearchTree* BST);

// Calculate height of the BST
int binarySearchTreeHeight(struct BinarySearchTree* BST);

// Clean up BST - deallocate node memory
void binarySearchTreeClear(struct BinarySearchTree* BST);


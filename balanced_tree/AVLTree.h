/*
 * AVL Tree, recursive implementaion.
 * AVL Trees are Binary Search Trees which balances itself
 * to keep operations logarithmic.
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
	// The value/data contained within the node.
	int data;

	// The left and right childern of this node.
	struct Node* left;
	struct Node* right; 

	// 'bf' is short for balance factor for AVL Tree.
	int bf;

	// The height of this node in the tree.
	int height;

}Node;

// Create AVL struct, it will hold the root and node counts
typedef struct AVLTree{
	// The root node of the AVL tree.
	struct Node* root;

	// Tracks the number of nodes inside the tree.
	int nodeCount;

	bool state; // check if the list is initialized/active or not
}BinarySearchTree;


/*
	 * Queue data structure for implementing level order traversal in AVL Tree
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
void queueInit(struct Queue* queue);

// Push an element to the queue, O(1).
void queuePush(struct Queue* queue, struct Node* treeNode);

// Pop an element off the queue, O(1).
struct Node* queuePop(struct Queue* queue);

// Clear all queue, O(n).
void queueClear(struct Queue* queue);

/*
	* End of Queue implimentation
*/

// Debug
void debugData(struct Node* node);

// Initialize AVL 
void avlTreeInit(struct AVLTree* AVL);

// Check if the AVL is active
bool avlTreeIsActive(struct AVLTree* AVL);

// Error handling if the AVL is inactive
void avlTreeState(struct AVLTree* AVL);

// Return the size of AVL.
int avlTreeSize(struct AVLTree* AVL);

// Check if the AVL is empty
bool avlTreeIsEmpty(struct AVLTree* AVL);

// Helper function compare data
int compareData(int a, int b);

// Helper recursive function to check if the data is in the tree
bool containsData(struct Node* node, int data);

// Helper method: find maximum between two numbers
int max(int a, int b);

// Helper function: Update a node's height and balance factor
void update(struct Node* node);

// Helper methods for balance the tree

struct Node* leftRotation(struct Node* node);

struct Node* rightRotation(struct Node* node);

struct Node* leftLeftCase(struct Node* node);

struct Node* leftRightCase(struct Node* node);

struct Node* rightRightCase(struct Node* node);

struct Node* rightLeftCase(struct Node* node);

// Re-balance a node if its balance factor is +2 or -2
struct Node* balance(struct Node* node);

// Helper function add a new node to AVL - recursive function
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
// In AVL this print data in increasing order
struct Node* inorderNode(struct Node* node);

// Postorder helper method print data after the recursive calls
struct Node* postorderNode(struct Node* node);

// Level order traverse helper method using queue
void levelorderNode(struct Node* node, int size);

// Print prettier tree
int printPretty(Node* node, int isLeft, int offset, int depth, char s[20][255]);

// Recursive helper method to compute the hight of the tree
int treeHeight(struct Node* node);

// Clear AVL - memory deallocate using postorder traverse recursion
struct Node* clearNode(struct Node* node);

// Check if the data exists in AVL Tree
bool avlTreeContains(struct AVLTree* AVL, int data);

// Add element to the AVL Tree
bool avlTreeAdd(struct AVLTree* AVL, int data);

// Remove a node from AVL
bool avlTreeRemove(struct AVLTree* AVL, int data);

// Travese AVL and print data
void avlTreePrintOrder(struct AVLTree* AVL, enum traverseOrder order);

// Print prettier AVL tree
void avlTreePrint(struct AVLTree* AVL);

// Calculate height of the AVL
int avlTreeHeight(struct AVLTree* AVL);

// Clean up AVL - deallocate node memory
void avlTreeClear(struct AVLTree* AVL);

#include <stdbool.h>

// Create Node.
typedef struct Node{
	int data;
	struct Node* next;
	struct Node* prev; // for doubly linked list
}Node;

// Create list struct to keep track of head, tail, size and type of linked list.
typedef struct List{
	struct Node* head;
	struct Node* tail;
	int size;
	bool doubly; // default this is a doubly linked list
	bool state;  // check if the list is initialized/active or not
}List;


// Only for internal debug test
void debugData(struct Node* node);

// Initialize linked list
struct List* listInit(bool doubly);

// Check if the list is active
bool listIsActive(struct List* list);
	
// Error handling if the list is inactive
void listState(struct List* list);
	
// Return the size of linked list.
int listSize(struct List* list);
	
// Check if the list is empty
bool listIsEmpty(struct List* list);

// Check if the list is doubly linked
bool listIsDoubly(struct List* list);

// Add an element to the tail of the linked list, O(1)
void listAddLast(struct List* list, int data);
	
// Add an element to the tail of the linked list, O(1)
void listAdd(struct List* list, int data);
	
// Push an element to the tail of the linked list, O(1)
void listPush(struct List* list, int data);
	
// Add an element to the begining of the list, O(1)
void listAddFirst(struct List* list, int data);
	
// Check the head data if exists, O(1)
int listPeekFirst(struct List* list);

// Check the tail data if exists, O(1)
int listPeekLast(struct List* list);

// Remove the first value at the head of the list, O(1)
int listRemoveFirst(struct List* list);
	
// Remove last value at the tail of the list, doubly: O(1), singly: O(n).
int listRemoveLast(struct List* list);
	
// Pop value at the end of the list, doubly: O(1), singly: O(n).
int listPop(struct List* list);
	
// Remove an arbitrary node from the linked list, O(1), O(n) - singly linked list.
int listRemoveNode(struct List* list, struct Node* node);
	
// Remove a node at a particular index, O(n).
int listRemoveAt(struct List* list, int index);
	
// Remove a particular value in the linked list, O(n);
bool listRemoveData(struct List* list, int data);
	
// Find the index of a particular value in the linked list, O(n).
int listIndexOf(struct List* list, int data);
	
// Check if a value is contained within the linked list, O(n).
bool listContains(struct List* list, int data);
	
// Reverse a linked list, O(n)
void listReverse(struct List* list);
	
// Cleanup and empty the list
void listClear(struct List* list);
	
// Print linked list data
void listPrint(struct List* list);

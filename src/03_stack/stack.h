/*

 * Stack data structure implimentation based on 
 	'linkedList' data structre.
 
 * linkedList implimentaion here is only using singly linked list
 	stack only need to keep track of top of the stack element (Head)
 
 * Please reference linkedList implimentaion on details.

*/

#include <stdbool.h>

// Create Node.
typedef struct Node{
	int data;
	struct Node* next;
}Node;


// Create stack struct to keep track of head, size and state of stack.
typedef struct Stack{
	struct Node* head;
	int size;
	bool state;
}Stack;

// Only for dev usage
void debugData(struct Node* node);

// Initialize stack
struct Stack* stackInit(void);

// Check if the stack is active
bool stackIsActive(struct Stack* stack);

// Error handling if the stack is inactive
void stackState(struct Stack* stack);

// Return the size of stack.
int stackSize(struct Stack* stack);

// Check if the stack is empty
bool stackIsEmpty(struct Stack* stack);

// Push an element to the stack, O(1).
void stackPush(struct Stack* stack, int data);

// Pop an element off the stack, O(1).
int stackPop(struct Stack* stack);

// Peek the top of the stack, O(1).
int stackPeek(struct Stack* stack);

// Clear all, O(n).
void stackClear(struct Stack* stack);

// Print pretty stack data, O(n)
void stackPrint(struct Stack* stack);


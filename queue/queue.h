/*

 * Queue data structure implimentation based on 
 	'linkedList' data structre.
 
 * linkedList implimentaion here is only using singly linked list
 	queue only need to keep track of head and tail of a linked list.
 
 * Please reference linkedList implimentaion on more details.

*/

#include <stdbool.h>

// Create Node.
typedef struct Node{
	int data;
	struct Node* next;
}Node;


// Create queue struct to keep track of head, tail, size and state of queue.
typedef struct Queue{
	struct Node* head;
	struct Node* tail;
	int size;
	bool state;
}Queue;

// Only for dev usage
void debugData(struct Node* node);

// Initialize queue
void queueInit(struct Queue* queue);

// Check if the queue is active
bool queueIsActive(struct Queue* queue);

// Error handling if the queue is inactive
void queueState(struct Queue* queue);

// Return the size of queue.
int queueSize(struct Queue* queue);

// Check if the queue is empty
bool queueIsEmpty(struct Queue* queue);

// Push an element to the queue, O(1).
void queuePush(struct Queue* queue, int data);

// Enqueue is same as push
void enqueue(struct Queue* queue, int data);

// Queue offer is same as push
void queueOffer(struct Queue* queue, int data);

// Pop an element off the queue, O(1).
int queuePop(struct Queue* queue);

// Dequeue is same as pop
int dequeue(struct Queue* queue);

// Queue poll is same as pop
int queuePoll(struct Queue* queue);

// Peek the top of the queue, O(1).
int queuePeek(struct Queue* queue);

// Clear all, O(n).
void queueClear(struct Queue* queue);

// Print pretty queue data, O(n)
void queuePrint(struct Queue* queue);

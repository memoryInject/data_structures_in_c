/*

 * Queue data structure implimentation based on 
 	'linkedList' data structre.
 
 * linkedList implimentaion here is only using singly linked list
 	queue only need to keep track of head and tail of a linked list.
 
 * Please reference linkedList implimentaion on more details.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "queue.h"

// Only for dev usage
void debugData(struct Node* node){
	printf("Debug Data: %d\n", node->data);
}

// Initialize queue
void queueInit(struct Queue* queue){
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
	queue->state = true; // activate the queue
}

// Check if the queue is active
bool queueIsActive(struct Queue* queue){
	return queue->state;
}

// Error handling if the queue is inactive
void queueState(struct Queue* queue){
	if(queue->state == false){
		printf("%s, inactive queue!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the size of queue.
int queueSize(struct Queue* queue){
	queueState(queue); // Check if the queue is active	
	return queue->size;
}

// Check if the queue is empty
bool queueIsEmpty(struct Queue* queue){
	queueState(queue);
	if(queue->size == 0){
		return true;
	}
	else{
		return false;
	}
}

// Push an element to the queue, O(1).
void queuePush(struct Queue* queue, int data){
	queueState(queue);
	if(queue->size == 0){
		// Allocate memory for head node.
		queue->head = (struct Node*) malloc(sizeof(struct Node));
		queue->head->data = data;
		queue->head->next = NULL;
		queue->tail = queue->head;
		queue->tail->next = NULL;
	}
	else{
		// Iterator for track current tail
		struct Node* iter = queue->tail;
		// Allocate memory for tail node.
		queue->tail = (struct Node*) malloc(sizeof(struct Node));
		queue->tail->data = data;
		queue->tail->next = NULL;
		iter->next = queue->tail;
	}
	// Increment size
	queue->size++;
}

// Enqueue is same as push
void enqueue(struct Queue* queue, int data){
	queuePush(queue, data);
}

// Queue offer is same as push
void queueOffer(struct Queue* queue, int data){
	queuePush(queue, data);
}

// Pop an element off the queue, O(1).
int queuePop(struct Queue* queue){
	queueState(queue);
	if(queueIsEmpty(queue)){
		printf("Queue is empty...");
		exit(EXIT_SUCCESS);
	}
	else{
		// Store the data for return in the end.
		int data = queue->head->data;
		// Store the original head for memory clean up.
		struct Node* iter = queue->head;
		queue->head = queue->head->next;
		free(iter);
		iter = NULL;
		--queue->size;
		return data;
	}
}

// Dequeue is same as pop
int dequeue(struct Queue* queue){ return queuePop(queue); };

// Queue poll is same as pop
int queuePoll(struct Queue* queue){ return queuePop(queue); };

// Peek the top of the queue, O(1).
int queuePeek(struct Queue* queue){
	queueState(queue);
	if(queueIsEmpty(queue)){
		printf("Queue is empty...");
		exit(EXIT_SUCCESS);
	}
	else{
		return queue->head->data;	
	}
}

// Clear all, O(n).
void queueClear(struct Queue* queue){
	queueState(queue);
	if(queueIsEmpty(queue)){
		printf("Queue is empty...");
		exit(EXIT_SUCCESS);
	}
	else{
		// Iterator for travese the queue
		struct Node* iter;
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
}

// Print pretty queue data, O(n)
void queuePrint(struct Queue* queue){
	queueState(queue);
	if(queueIsEmpty(queue)){
		printf("Queue is empty...");
		exit(EXIT_SUCCESS);
	}
	else{
  		int size = queue->size;
  		struct Node* iter = queue->head;

  		for(int i=0; i<size-1; i++){
			printf("[ %d ]\n", iter->data);
  			iter = iter->next;
  		}
	}
}

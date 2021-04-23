/*

 * Stack data structure implimentation based on 
 	'linkedList' data structre.
 
 * linkedList implimentaion here is only using singly linked list
 	stack only need to keep track of top of the stack element (Head)
 
 * Please reference linkedList implimentaion on details.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "stack.h"

// Debug
void debugData(struct Node* node){
	printf("Debug Data: %d\n", node->data);
}

// Initialize stack
struct Stack* stackInit(){
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
	stack->head = NULL;
	stack->size = 0;
	stack->state = true; // activate the stack 

	return stack;
}

// Check if the stack is active
bool stackIsActive(struct Stack* stack){
	return stack->state;
}

// Error handling if the stack is inactive
void stackState(struct Stack* stack){
	if(stack->state == false){
		printf("%s, inactive stack!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the size of stack.
int stackSize(struct Stack* stack){
	stackState(stack); // Check if the stack is active	
	return stack->size;
}

// Check if the stack is empty
bool stackIsEmpty(struct Stack* stack){
	stackState(stack);
	if(stack->size == 0){
		return true;
	}
	else{
		return false;
	}
}

// Push an element to the stack, O(1).
void stackPush(struct Stack* stack, int data){
	stackState(stack);
	if(stack->size == 0){
		// Manually allocate memory for each new nodes.
		stack->head = (struct Node*) malloc(sizeof(struct Node));
		stack->head->data = data;
		stack->head->next = NULL;
	}
	else{
		struct Node* iter = stack->head; // Iterator for current head
		// Manually allocate memory for each new nodes.
		stack->head = (struct Node*) malloc(sizeof(struct Node));
		stack->head->data = data;
		stack->head->next = iter;
		iter = NULL;
	}
	stack->size++;
}

// Pop an element off the stack, O(1).
int stackPop(struct Stack* stack){
	stackState(stack);
	if(stackIsEmpty(stack)){
		printf("Stack is empty...");
		exit(EXIT_SUCCESS);
	}
	else{
		int data = stack->head->data;
		struct Node* iter = stack->head;
		stack->head = stack->head->next;
		free(iter);
		iter = NULL;
		return data;
		--stack->size;
	}
}

// Peek the top of the stack, O(1).
int stackPeek(struct Stack* stack){
	stackState(stack);
	if(stackIsEmpty(stack)){
		printf("Stack is empty...");
		exit(EXIT_SUCCESS);
	}
	else{
		return stack->head->data;	
	}
}

// Clear all, O(n).
void stackClear(struct Stack* stack){
	stackState(stack);
	if(stackIsEmpty(stack)){
		printf("Stack is empty...");
		printf("Clear empty stack...");
		free(stack);
		exit(EXIT_SUCCESS);
	}
	else{
		// Iterator for travese the stack
		struct Node* iter;
		while(stack->head){
			iter = stack->head;
			stack->head = stack->head->next;
			// Free up the memory used by node
			free(iter);
			iter = NULL;
		}
		stack->head = NULL;
		stack->size = 0;
		free(stack);
	}
}

// Print pretty stack data, O(n)
void stackPrint(struct Stack* stack){
	stackState(stack);
	if(stackIsEmpty(stack)){
		printf("Stack is empty...");
		exit(EXIT_SUCCESS);
	}
	else{
  		int size = stack->size;
  		struct Node* iter = stack->head;

  		for(int i=0; i<size-1; i++){
			printf("[ %d ]\n", iter->data);
  			iter = iter->next;
  		}
	}
}


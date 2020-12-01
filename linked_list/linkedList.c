#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "linkedList.h"

// Debug
void debugData(struct Node* node){
	printf("Debug Data: %d\n", node->data);
}

// Initialize linked list
void listInit(struct List* list, bool doubly){
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->doubly = doubly;
	list->state = true; // activate the list
}

// Check if the list is active
bool listIsActive(struct List* list){
	return list->state;
}

// Error handling if the list is inactive
void listState(struct List* list){
	if(list->state == false){
		printf("%s, inactive list!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the size of linked list.
int listSize(struct List* list){
	listState(list); // Check if the list is active	
	return list->size;
}

// Check if the list is empty
bool listIsEmpty(struct List* list){
	listState(list);
	if(list->size == 0){
		return true;
	}
	else{
		return false;
	}
}

// Check if the list is doubly linked
bool listIsDoubly(struct List* list){
	listState(list);
	return list->doubly;
}

// Add an element to the tail of the linked list, O(1)
void listAddLast(struct List* list, int data){
	listState(list);
	if(listIsEmpty(list)){
		list->head = (struct Node*)malloc(sizeof(struct Node));
		
		// Set head and tail to reference same node 
		list->head->data = data;
		list->tail = list->head;

		// Set head next and tail next to NULL
		list->head->next = NULL;
		list->tail->next = NULL;

		// Check if the list is doubly then set head and tail prev node
		if(list->doubly){
			list->head->prev = NULL;
			list->tail->prev = NULL;
		}
	}
	else{
		struct Node* iter = list->tail; // Iterator for current tail
		list->tail->next = (struct Node*)malloc(sizeof(struct Node));
		list->tail->next->data = data;
		list->tail = list->tail->next;
		list->tail->next = NULL;

		// Check if the list size is 1 then set head next
		if(list->size == 1){
			list->head->next = list->tail;
		}
		
		// Check if the list is doubly
		if(list->doubly){
			list->tail->prev = iter;
		}
	}
	list->size++;
}

// Add an element to the tail of the linked list, O(1)
void listAdd(struct List* list, int data){
	listAddLast(list, data);
}

// Push an element to the tail of the linked list, O(1)
void listPush(struct List* list, int data){
	listAddLast(list, data);
}

// Add an element to the begining of the list, O(1)
void listAddFirst(struct List* list, int data){
	listState(list); // Check if the list is active
	if(listIsEmpty(list)){
		list->head = (struct Node*) malloc(sizeof (struct Node));
		list->head->data = data;
		list->tail = list->head;
		list->head->next = NULL;
		list->tail->next = NULL;
		if(listIsDoubly(list)){
			list->head->prev = NULL;
			list->tail->prev = NULL;
		}
	}
	else{
		struct Node* iter = list->head;
		list->head = (struct Node*) malloc(sizeof (struct Node));
		list->head->data = data;
		list->head->next = iter;
		if(listIsDoubly(list)){
			list->head->prev = NULL;
		}
	}
	list->size++;
}

// Check the head data if exists, O(1)
int listPeekFirst(struct List* list){
	listState(list);
	if(listIsEmpty(list)){
		printf("Empty list\n");
		exit(EXIT_FAILURE);
	}
	return list->head->data;
}

// Check the tail data if exists, O(1)
int listPeekLast(struct List* list){
	listState(list);
	if(listIsEmpty(list)){
		printf("Empty list\n");
		exit(EXIT_FAILURE);
	}
	return list->tail->data;
}

// Remove the first value at the head of the list, O(1)
int listRemoveFirst(struct List* list){
	listState(list); // Check if its a valid list
	if(listIsEmpty(list)){
		printf("Empty list\n");
		exit(EXIT_FAILURE);
	}
	
	struct Node* iter = list->head; // Create an iterator for later clean up
	int data = list->head->data;
	
	list->head = list->head->next;
	--list->size;

	// After move the head check if its empty
	if(listIsEmpty(list)){
		list->tail = NULL;
		list->tail->prev = NULL;
		list->tail->next = NULL;
		list->head->next = NULL;
	}

	// Clean up
	list->head->prev = NULL;
	free(iter);
	iter = NULL;

	return data;
}

// Remove last value at the tail of the list, doubly: O(1), singly: O(n).
int listRemoveLast(struct List* list){
	listState(list); // Check if its active
	if(listIsEmpty(list)){
		printf("Empty list\n");
		exit(EXIT_FAILURE);
	}
	
	// Collect the data for return
	int data = list->tail->data;
	struct Node* iter = list->head; // Create an iterator for singly list
	// Check if the list is doubly
	if(listIsDoubly(list)){
		// Move tail pointer to prev node
		list->tail = list->tail->prev;
		// Cleanup
		free(list->tail->next);
		list->tail->next = NULL;
	}
	else{
		// For singly linked list
		// Loop through the list until before the tail
		while(iter->next != list->tail){
			iter = iter->next;
		}
		// Move the tail pointer to iter
		list->tail = iter;

		// Cleanup
		free(iter->next);
		iter->next = NULL;
		list->tail->next = NULL;
	}

	// Subtract list size by one
	--list->size;
	// Return the data from removed node
	return data;
}

// Pop value at the end of the list, doubly: O(1), singly: O(n).
int listPop(struct List* list){
	return listRemoveLast(list);
}

// Remove an arbitrary node from the linked list, O(1), O(n) - singly linked list.
int listRemoveNode(struct List* list, struct Node* node){
	// Check if the list is active
	listState(list);
	// Check if the node to remove is either head or tail and handle those seperately
	if(node == list->head){ return listRemoveFirst(list); }
	if(node == list->tail){ return listRemoveLast(list); }

	// Store the data for return in the end
	int data = node->data;
	// Check if the list is doubly
	if(listIsDoubly(list)){
		// Make the pointer of the adjacent nodes skip over 'node'.
		node->next->prev = node->prev;
		node->prev->next = node->next;

		// Cleanup
		free(node);
		node->next = NULL;
		node->prev = NULL;
		node = NULL;
	}
	else{
		// Singly linked list, O(n)
		struct Node* iter = list->head; // Iterator for find the node previous
		while(iter->next != node){
			// Get the previous node connected to the node.
			iter = iter->next;
		}
		// Make the previous node skip over the 'node'.
		iter->next = node->next;

		// Cleanup.
		free(node);
		node->next = NULL;
		node = NULL;
	}

	// Decrease list size by one
	--list->size;

	// Return the removed node data
	return data;
}

// Remove a node at a particular index, O(n).
int listRemoveAt(struct List* list, int index){
	// Check if the list is active
	listState(list);
	// Make sure the index provided is valid
	if(index < 0 || index >= list->size){
		printf("Invalid index. \n");
		exit(EXIT_FAILURE);
	}

	// Create an iterator for searching node.
	struct Node* iter; 
	// Check if the list is doubly.
	if(listIsDoubly(list)){ // Doubly linkded list
		// Search from the front of the list.
		if(index < list->size/2){
			iter = list->head;
			for(int i = 0; i != index; i++){
				iter = iter->next;
			}
		}
		else{ // Search from the back of the list.
			iter = list->tail;
			for(int i = list->size - 1; i != index; --i){
				iter = iter->prev;
			}
		}
		return listRemoveNode(list, iter);
	}
	else{ // Singly linked list.
		iter = list->head;
		for (int i = 0; i != index; i++){
			iter = iter->next;
		}
		return listRemoveNode(list, iter);
	}
}

// Remove a particular value in the linked list, O(n);
bool listRemoveData(struct List* list, int data){
	// Check if the list is active
	listState(list);
	// Iterator for traverse the list
	struct Node* iter = list->head;
	while(iter != NULL){
		if(iter->data == data){
			// Remove the node and return true
			listRemoveNode(list, iter);
			return true;
		}
		iter = iter->next;
	}
	return false;
}

// Find the index of a particular value in the linked list, O(n).
int listIndexOf(struct List* list, int data){
	// Check if the list is active
	listState(list);
	// Iterator for traverse the list
	struct Node* iter = list->head;
	for (int i = 0; i < list->size; i++){
		if(iter->data == data){
			return i;
		}
		iter = iter->next;
	}
	return -1;
}

// Check if a value is contained within the linked list, O(n).
bool listContains(struct List* list, int data){
	return listIndexOf(list, data) != -1 ? true : false;
}

// Reverse a linked list, O(n)
void listReverse(struct List* list){
	// Check if the list is active
	listState(list);
	// Check if the list is doubly
	if (listIsDoubly(list)){
		// Iterator for traverse the list
		struct Node* iter = list->head;
		// Helper node
		struct Node* next = NULL;
		while(iter != NULL){
			next = iter->next;
			iter->next = iter->prev;
			iter->prev = next;
			iter = next;
		}
		iter = list->head;
		list->head = list->tail;
		list->tail = iter;
		iter = NULL;
		next = NULL;
	}
	else{
		// Singly linked list
		// Iterator for traverse the list
		struct Node* iter = list->head;
		// Helper nodes
		struct Node* next = NULL;
		struct Node* prev = NULL;
		while(iter != NULL){
			next = iter->next; // store head.next node to next.
			iter->next = prev; // reverse the list connection.
			prev = iter; 	   // move prev to head.
			iter = next;	   // move head to next.
		}
		iter = list->head;
		list->head = list->tail;
		list->tail = iter;
		iter = NULL;
		next = NULL;
		prev = NULL;
	}
}

// Cleanup and empty the list
void listClear(struct List* list){
	listState(list);
	struct Node* iter = list->head;
	while(iter != NULL){
		struct Node* next = iter->next;
		free(iter);
		iter->next = NULL;
		iter->prev = NULL;
		iter = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	iter = NULL;
}

// Print linked list data
void listPrint(struct List* list){
	listState(list);
	struct Node* iter = list->head;
	if(listIsDoubly(list)){
		printf("\nSize of linked list: %d\n", list->size);
		printf("Type of linked list: Doubly\n\n");
		while(iter != NULL){
			printf("[%d]<->", iter->data);
			iter = iter->next;
		}
		printf("NULL\n\n");
	}
	else{
		printf("\nSize of linked list: %d\n", list->size);
		printf("Type of linked list: singly\n\n");
		while(iter != NULL){
			printf("[%d]->", iter->data);
			iter = iter->next;
		}
		printf("NULL\n\n");
	}
}

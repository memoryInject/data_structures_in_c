#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"

// Initialize array element
void initArray(Array* a, size_t initialSize){
	a->array = malloc(initialSize * sizeof(int));
	a->used = 0;
	a->size = initialSize;
}

// Insert elements to array
void insertArray(Array* a, int element){
	if(a->used == a->size){
		a->size *= 2;
		a->array = realloc(a->array, a->size * sizeof(int));
	}
	a->array[a->used++] = element;
}

// Push element to array same as insert
void pushArray(Array* a, int element){
	insertArray(a, element);
}

// Free array memory

void freeArray(Array* a){
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

// Pop element from array
void popArray(Array* a){
	a->array[a->used] = 0;
	a->used--;
}

// Print array elements
void printArray(Array* a){
	if(a->used != 0){
		for(int i = 0; i < a->used; ++i){
			printf("%d ", a->array[i]);
		}
		printf("\n");
	}
	else{
		printf("empty array\n");
	}
}


/*
	* Union Find/Disjoint Set data structure implementaion in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "unionFind.h"

// Initialize UnionFind with size
struct UnionFind* unionFindInit(int size){
	if(size <= 0){
		printf("Size must be above 0.\n");
		exit(EXIT_FAILURE);
	}

	struct UnionFind* uf = (struct UnionFind*) malloc(sizeof(struct UnionFind));

	uf->size = size;
	uf->numComponents = size;
	uf->sz = (int*) malloc(sizeof(int) * size);
	uf->id = (int*) malloc(sizeof(int) * size);

	for(int i = 0; i < size; i++){
		uf->id[i] = i; // Link to itself (self root)
		uf->sz[i] = 1; // Each component is originally of size one 
	}

	uf->state = true;

	return uf;
}

// Check if the union find is active
bool unionFindIsActive(struct UnionFind* uf){
	return uf->state;
}

// Error handling if the union find is inactive
void unionFindState(struct UnionFind* uf){
	if(uf->state == false){
		printf("%s, inactive union find!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the number of elements in this UnionFind/Disjoint set
int unionFindSize(struct UnionFind* uf){
	unionFindState(uf); // Check if the union find is active
	return uf->size;
}

// Find which component/set 'p' belongs to, takes amortized constant time.
int unionFindFind(struct UnionFind* uf, int p){
	unionFindState(uf);
	
	// Find the root of the component/set
	int root = p;
	while(root != uf->id[root]){
		root = uf->id[root]; 
	}

	// Compress the path leading back to the root.
	// Doing this operation is called 'path compression'
	// and is waht gives us amortized time complexity
	while(p != root){
		int next = uf->id[p];
		uf->id[p] = root;
		p = next;
	}

	return root;
}

// Return whether or not the elements 'p' and 
// 'q' are in the same components/set.
bool unionFindConnected(struct UnionFind* uf, int p, int q){
	unionFindState(uf);
	return unionFindFind(uf, p) == unionFindFind(uf, q);
}

// Return the size of the components/set 'p' belongs to
int unionFindComponentSize(struct UnionFind* uf, int p){
	unionFindState(uf);
	return uf->sz[unionFindFind(uf, p)];
}

// Return the number of remaining components/sets
int unionFindComponents(struct UnionFind* uf){
	unionFindState(uf);
	return uf->numComponents;
}

// Unify the components/sets containing elements 'p' and 'q'
void unionFindUnify(struct UnionFind* uf, int p, int q){
	unionFindState(uf);

	int root1 = unionFindFind(uf, p);
	int root2 = unionFindFind(uf, q);
	
	// These elements are already in the same group!
	if(root1 == root2){
		return;
	}

	// Merge smaller component/set into the larger one.
	if(uf->sz[root1] < uf->sz[root2]){
		uf->sz[root2] += uf->sz[root1];
		uf->id[root1] = root2;
	}
	else{
		uf->sz[root1] += uf->sz[root2];
		uf->id[root2] = root1;
	}

	// Since the roots found are different we know that the
	// number of components/sets has decreased by one
	--uf->numComponents;
}

// Clear memory for union find
void unionFindClear(struct UnionFind* uf){
	unionFindState(uf);
	
	// Deallocate memory
	free(uf->sz);
	free(uf->id);
	// Set size and numComponents to zero 
	uf->size = 0;
	uf->numComponents = 0;
	// Deactivate union find
	uf->state = false;

	free(uf);
}

// Pretty print union find
void unionFindPrint(struct UnionFind* uf){
	unionFindState(uf);
	printf("    i: ");
	for(int i = 0; i < uf->size; i++){
		printf("%d ", i);
	}
	printf("\n");

	printf("id[i]: ");
	for(int i = 0; i < uf->size; i++){
		printf("%d ", uf->id[i]);
	}
	printf("\n");

	printf("sz[i]: ");
	for(int i = 0; i < uf->size; i++){
		printf("%d ", uf->sz[i]);
	}
	printf("\n\n");

	printf("Components left: %d\n", unionFindComponents(uf));
}


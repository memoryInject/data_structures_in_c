/*
	* Union Find/Disjoint Set data structure implementaion in C.
*/

#include <stdbool.h>

typedef struct UnionFind {
	// Number of elements in this union find
	int size;
	// Used to track the size of each of the component (point to an array)
	int* sz;
	// id[i] point to the parent of i, if id[i] = i then i is a root node
	int* id;
	// Track the number of components in the union find 
	int numComponents;
	// State of this union find active/deactive
	bool state;
}UnionFind;

// Initialize UnionFind with size
void unionFindInit(struct UnionFind* uf, int size);

// Check if the union find is active
bool unionFindIsActive(struct UnionFind* uf);

// Error handling if the union find is inactive
void unionFindState(struct UnionFind* uf);

// Return the number of elements in this UnionFind/Disjoint set
int unionFindSize(struct UnionFind* uf);

// Find which component/set 'p' belongs to, takes amortized constant time.
int unionFindFind(struct UnionFind* uf, int p);

// Return whether or not the elements 'p' and 
// 'q' are in the same components/set.
bool unionFindConnected(struct UnionFind* uf, int p, int q);

// Return the size of the components/set 'p' belongs to
int unionFindComponentSize(struct UnionFind* uf, int p);

// Return the number of remaining components/sets
int unionFindComponents(struct UnionFind* uf);

// Unify the components/sets containing elements 'p' and 'q'
void unionFindUnify(struct UnionFind* uf, int p, int q);

// Clear memory for union find
void unionFindClear(struct UnionFind* uf);

// Pretty print union find
void unionFindPrint(struct UnionFind* uf);	

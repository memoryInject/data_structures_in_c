#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "unionFind.h"

// Driver test code
int main(int argc, char* argv[])
{
	printf("UnionFind data structure tests...\n\n");
	
	// Create UnionFInd
	struct UnionFind* uf = unionFindInit(10);
	printf("Union Find Active: %s, with sizeof %d\n\n", unionFindIsActive(uf) == true ? "true" : "false", unionFindSize(uf));
	
	// let p=5 and q=6
	int p = 5;
	int q = 6;
	printf("Let, p = %d, q = %d\n\n", p, q);

	// Find which component/ set p belongs to
	printf("p belong to id[p]: %d, component/set\n",unionFindFind(uf, p));
	printf("q belong to id[q]: %d, component/set\n\n",unionFindFind(uf,q));

	// Check if p and q are connected
	printf("p and q are connected: %s\n\n", unionFindConnected(uf, p, q) == true ? "true" : "false");
	
	// Unify components/sets containing p and q
	printf("Unify p and q components\n\n");
	unionFindUnify(uf, p, q);
	
	// Find which component/ set p belongs to after unify
	printf("p belong to id[p]: %d, component/set after unify\n",unionFindFind(uf, p));
	printf("q belong to id[q]: %d, component/set after unify\n\n",unionFindFind(uf,q));

	// Check if p and q are connected
	printf("p and q are connected: %s\n\n", unionFindConnected(uf, p, q) == true ? "true" : "false");
	
	// Component size of p belongs
	printf("Component size of p belong is: %d\n\n", unionFindComponentSize(uf, p));

	// Pretty print union find
	unionFindPrint(uf);

	// Clean up memory
	unionFindClear(uf);
	printf("\nClear union find..\n\n");

	return 0;
}

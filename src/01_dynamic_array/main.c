#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"

int main(int argc, char* argv[])
{
	Array* a = initArray(5); // 5 elements initialized
	
	int i;
	for(i = 0; i < 10; i++){
		insertArray(a, i); // insert element to array
	}

	printArray(a); // print array elements
	printf("Size: %ld\n", a->used); // print current used units

	popArray(a); // remove an element in the array
	printArray(a); 
	printf("Size: %ld\n", a->used);

	pushArray(a, 13); // push an element to the array
	printArray(a);
	printf("Size: %ld\n", a->used);

	freeArray(a); // free up memory

	return 0;
}

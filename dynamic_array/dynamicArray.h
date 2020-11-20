// Init array struct 

typedef struct{
	int* array; 	// pointer to the array
	size_t used;	// currently used space in the array
	size_t size;	// total space in the array
}Array;

// Initialize array element
void initArray(Array* a, size_t initialSize);

// Insert elements to array
void insertArray(Array* a, int element);

// Push element to array same as insert
void pushArray(Array* a, int element);

// Free array memory
void freeArray(Array* a);

// Pop element from array
void popArray(Array* a);

// Print array elements
void printArray(Array* a);


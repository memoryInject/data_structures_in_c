/*
 * C implementation of a Suffix Array Data Structure includes Least Common
 * Prefix(LCP) Array
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdbool.h>

// Create suffix array struct to store both suffix array and lcp array
typedef struct SuffixArray {
	// Length of suffix array
	int N;
	// T is the text
	char T[256];
	// The sorted suffix array values.
	int* sa;
	// Longest common prefix array
	int* lcp;

	bool constructedSa;
	bool constructedLcpArray;
	bool state; // Check if the SuffixArray is initialized/active or not

}SuffixArray;

// Helper method: Build suffix array
void construct(struct SuffixArray* sa);

// Helper method: Build lcp array using already built suffix array;
void kasai(struct SuffixArray* sa);

// Initialize Suffix Array
void suffixArrayInit(struct SuffixArray* sa, char* text, int len);

// Check if the SuffixArray  is active
bool suffixArrayIsActive(struct SuffixArray* sa);

// Error handling if the list is inactive
void suffixArrayState(struct SuffixArray* sa);

// Return the size of suffix array
int suffixArraySize(struct SuffixArray* sa);

// Get suffix array as a int*
int* suffixArrayGetSA(struct SuffixArray* sa);

// Get LCP array as a int*
int* suffixArrayGetLCP(struct SuffixArray* sa);

// Print pretty suffix array and lcp array
void suffixArrayPrint(struct SuffixArray* sa);

// Clean up memory and clear SuffixArray
void suffixArrayClear(struct SuffixArray* sa);


/* START OF BUILDING SUFFIX ARRAY */

// C implementaion of building suffix array of a given text
// Overall time complexity is O(nlognlogn)
// For sorting the array we implement mergeSort here which has time
// complexity of O(nlogn)

// Detailed explanation for this particular implementaion: 
// https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/

// Structure to store information of a suffix
typedef struct Suffix{
	int index; // To store original index
	int rank[2]; // To store ranks and next rank pair
}Suffix;

// Struct to store array of suffixes and size
typedef struct Suffixes{
	struct Suffix* suffix;
	int size;
}Suffixes;

// A comparison function used by mergeSort() to compare two suffixes
// Compare two pairs, return 1 if first pair is smaller
// Compare Suffix with rank and next rank (rank[0] and rank[1])
// if both are equal then compare with index 
bool cmp(struct Suffix a, struct Suffix b);

// Helper method for mergeSort: Merge two sorted Suffix arrays 
struct Suffixes* merge(struct Suffixes* a, struct Suffixes* b);

// mergeSort is a recursive function
struct Suffixes* mergeSort(struct Suffixes* arr);

// This is the main function that builds the suffix array
void construct(struct SuffixArray* sa);

/* END OF BUILDING SUFFIX ARRAY */


/* START OF BUILDING LCP ARRAT */

// Helper method: Use Kasai algorithm to build LCP array
// http://www.mi.fu-berlin.de/wiki/pub/ABI/RnaSeqP4/suffix-array.pdf

// C implementaion of creating lcp array using kasai's algorithm
// More detail of this implementation: 
// https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/

void kasai(struct SuffixArray* sa);

/* END OF BUILDING LCP ARRAY */

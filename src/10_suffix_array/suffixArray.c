/*
 * C implementation of a Suffix Array Data Structure includes Least Common
 * Prefix(LCP) Array
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "suffixArray.h"

// Initialize Suffix Array
struct SuffixArray* suffixArrayInit(char* text, int len){
	struct SuffixArray* sa = (struct SuffixArray*) malloc(sizeof(struct SuffixArray));
	strcpy(sa->T, text); // Store incoming string to T;
	sa->N = len;
	construct(sa);
	kasai(sa);
	sa->state = true;

	return sa;
}

// Check if the SuffixArray  is active
bool suffixArrayIsActive(struct SuffixArray* sa){
	return sa->state;
}

// Error handling if the list is inactive
void suffixArrayState(struct SuffixArray* sa){
	if(sa->state == false){
		printf("%s, inactive suffix array!!\n", strerror(1));
		exit(EXIT_FAILURE);
	}
}

// Return the size of suffix array
int suffixArraySize(struct SuffixArray* sa){
	suffixArrayState(sa);
	return sa->N;
}

// Get suffix array as a int*
int* suffixArrayGetSA(struct SuffixArray* sa){
	suffixArrayState(sa);
	return sa->sa;
}

// Get LCP array as a int*
int* suffixArrayGetLCP(struct SuffixArray* sa){
	suffixArrayState(sa);
	return sa->lcp;
}

// Print pretty suffix array and lcp array
void suffixArrayPrint(struct SuffixArray* sa){
	suffixArrayState(sa);

	printf("Suffix array for: %s\n", sa->T);
	for(int i = 0; i < sa->N; i++){
		printf("%d ", sa->sa[i]);
	}
	printf("\n\n");
	
	printf("LCP array for: %s\n", sa->T);
	for(int i = 0; i < sa->N; i++){
		printf("%d ", sa->lcp[i]);
	}
	printf("\n");
}

// Clean up memory and clear SuffixArray
void suffixArrayClear(struct SuffixArray* sa){
	suffixArrayState(sa);
	
	// Deallocate memory for sa, lcp
	free(sa->sa);
	free(sa->lcp);
	
	// Set text to none
	strcpy(sa->T, "");
	sa->N = 0;
	sa->constructedSa = false;
	sa->constructedLcpArray = false;
	sa->state = false; // Deactivate the struct

	free(sa);
}


/* START OF BUILDING SUFFIX ARRAY */

// C implementaion of building suffix array of a given text
// Overall time complexity is O(nlognlogn)
// For sorting the array we implement mergeSort here which has time
// complexity of O(nlogn)

// Detailed explanation for this particular implementaion: 
// https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/

// A comparison function used by mergeSort() to compare two suffixes
// Compare two pairs, return 1 if first pair is smaller
// Compare Suffix with rank and next rank (rank[0] and rank[1])
// if both are equal then compare with index 
bool cmp(struct Suffix a, struct Suffix b){
	if(a.rank[0] == b.rank[0]){
		if(a.rank[1] == b.rank[1]){
			if(a.index < b.index){
				return true;
			} else {
				return false;
			}
		} else if (a.rank[1] < b.rank[1]){
			return true;
		} else {
			return false;
		}
	} else {
		if(a.rank[0] < b.rank[0]){
			return true;
		} else {
			return false;
		}
	}
}

// Helper method for mergeSort: Merge two sorted Suffix arrays 
struct Suffixes* merge(struct Suffixes* a, struct Suffixes* b){
	// Create two iterator to keep track of elements
	int i = 0, j = 0;
	// Create an Suffixes for return
	struct Suffixes*  arrMerge = (struct Suffixes*) malloc(sizeof(struct Suffixes));
	// Allocate memory for merged array suffix
	arrMerge->suffix = (struct Suffix*) malloc(sizeof(struct Suffix) * (a->size + b->size));
	arrMerge->size = a->size + b->size;
	// Iterator for keep track of arrMerge index
	int k = 0;
	while(i < a->size && j < b->size){
		if(cmp(a->suffix[i], b->suffix[j])){
			arrMerge->suffix[k] = a->suffix[i];
			i++;
			k++;
		} else {
			arrMerge->suffix[k] = b->suffix[j];
			j++;
			k++;
		}
	}

	// Add rest of the elements to arrMerge
	while(i < a->size){
		arrMerge->suffix[k] = a->suffix[i];
		i++;
		k++;
	}

	while(j < b->size){
		arrMerge->suffix[k] = b->suffix[j];
		j++;
		k++;
	}

	// Clean up incoming arrays
	free(a->suffix);
	free(b->suffix);
	return arrMerge;
}

// mergeSort is a recursive function
struct Suffixes* mergeSort(struct Suffixes* arr){
	// Base case for recursion
	if(arr->size <= 1) return arr;
	// Find the mid points for spliting array into halves
	int midLo = arr->size/2;
	int midHi = arr->size - midLo;

	// Split array into two halves
	// Create arrays for store splits
	struct Suffixes splitLo;
	struct Suffixes splitHi;
	// Allocate memory for 'array' Suffix in two splits
	splitLo.suffix = (struct Suffix*) malloc(sizeof(struct Suffix) * midLo);
	splitHi.suffix = (struct Suffix*) malloc(sizeof(struct Suffix) * midHi);
	// Add size info to SuffixArrys
	splitLo.size = midLo;
	splitHi.size = midHi;
	// Fill the half arrays
	memcpy(splitLo.suffix, arr->suffix, midLo * sizeof(struct Suffix));
	memcpy(splitHi.suffix, arr->suffix + midLo, midHi * sizeof(struct Suffix));
	// Recursivly split the array into smallest level
	struct Suffixes* left = mergeSort(&splitLo);
	struct Suffixes* right = mergeSort(&splitHi);

	// Merge two halves together and return sorted array
	return merge(left, right);
}

// This is the main function that builds the suffix array
void construct(struct SuffixArray* sa){
	// Struct to store suffixes and their indexes
	struct Suffixes sfxs; 
	sfxs.size = sa->N;
	// Allocate memory for suffixes
	sfxs.suffix = (struct Suffix*) malloc(sizeof(struct Suffix) * sa->N);
	
	// Store suffixes and their indexes in an array of structures.
	// The structure is needed to sort the suffixes alphabatically
	// and maintain their old indexes while sorting
	for (int i = 0; i < sa->N; i++){
		sfxs.suffix[i].index = i;
		sfxs.suffix[i].rank[0] = sa->T[i] - 'a';
		sfxs.suffix[i].rank[1] = ((i+1) < sa->N) ? (sa->T[i+1] - 'a') : -1;
	}

	// Sort the suffixes using the comparison function
	struct Suffixes* sortedArray = mergeSort(&sfxs);	
	// Deallocate memory for sfxs.suffix since mergeSort retruns 
	// brand new Suffixes we do not need sfxs any more.
	free(sfxs.suffix);
	
	// At this point all the suffixes are sorted according to first
	// 2 characters. Lets sort suffixes according to first 4 
	// chracters, then first 8 and so on
	int* ind = (int*) malloc(sizeof(int) * sa->N); // This array is needed to 
				// get the index in suffixes from original index. 
				// This mapping needed to get next suffix.
	for (int k = 4; k < 2*sa->N; k = k*2){
		// Assigning rank and index values to first suffix
		int rank = 0;
		int prev_rank = sortedArray->suffix[0].rank[0];
		sortedArray->suffix[0].rank[0] = rank;
		ind[sortedArray->suffix[0].index] = 0;

		// Assigning rank to suffixes
		for(int i = 1; i < sa->N; i++){
			// If the first rank and next ranks are sfxsme as that of previous
			// suffix in array, assign the sfxsme new rank to this suffix
			if(sortedArray->suffix[i].rank[0] == prev_rank && sortedArray->suffix[i].rank[1] == sortedArray->suffix[i-1].rank[1]){
				prev_rank = sortedArray->suffix[i].rank[0];
				sortedArray->suffix[i].rank[0] = rank;
			} else { // Otherwise increment rank and assign
				prev_rank = sortedArray->suffix[i].rank[0];
				sortedArray->suffix[i].rank[0] = ++rank;
			}
			ind[sortedArray->suffix[i].index] = i;
		}
		
		// Assign next rank to every suffix
		for(int i = 0; i < sa->N; i++){
			int nextIndex = sortedArray->suffix[i].index + k/2;
			sortedArray->suffix[i].rank[1] = (nextIndex < sa->N) ? sortedArray->suffix[ind[nextIndex]].rank[0] : -1;
		}

		// Sort the suffixes according to first k characters
		// We need to create new sortedArray since the mergeSort returns
		// brand new arrays every time 😥
		struct Suffixes* sortedArrayNew = mergeSort(sortedArray);
		// Deallocate memory for sortedArray's suffix
		free(sortedArray->suffix);
		// Reassign sortedArray, since sortedArrayNew only live inside this
		// context we need to clean memory for each iteration of k
		sortedArray = sortedArrayNew;
	}
	
	// Deallocate memory for ind
	free(ind);
	
	// Store indexes of all sorted suffixes in the suffix array
	sa->sa = (int*) malloc(sizeof(int) * sa->N);
	for(int i = 0; i < sa->N; i++){
		sa->sa[i] = sortedArray->suffix[i].index;
	}

	// Deallocate sortedArray suffix
	free(sortedArray->suffix);

	// Set true for suffix array construction 
	sa->constructedSa = true;
	
}

/* END OF BUILDING SUFFIX ARRAY */


/* START OF BUILDING LCP ARRAT */

// Helper method: Use Kasai algorithm to build LCP array
// http://www.mi.fu-berlin.de/wiki/pub/ABI/RnaSeqP4/suffix-array.pdf

// C implementaion of creating lcp array using kasai's algorithm
// More detail of this implementation: 
// https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/

void kasai(struct SuffixArray* sa){
	// Allocate memory to store lcp array
	sa->lcp = (int*) malloc(sizeof(int) * sa->N);
	
	// An auxiliary array to store inverse of suffix array
	// elements. For example if suffixArr[0] is 5, the
	// invSuff[5] would store 0. this is used to get next
	// suffix string from suffix array.
	int* invSuff= (int*) malloc(sizeof(int) * sa->N);

	// Fill values in invSuff[]
	for(int i = 0; i < sa->N; i++){
		invSuff[sa->sa[i]] = i;
	}
	
	// Initialize length of previous LCP
	int k = 0;
	
	// Process all suffixes one by one starting from
	// first suffix in txt[]
	for(int i=0; i < sa->N; i++){
		// If the current suffix is at n-1, the we don't have next 
		// substring to consider. so lcp is not defined for this 
		// substring, we put zero.
		if(invSuff[i] == sa->N-1){
			k = 0;
			continue;
		}

		// j contains index of the next substring to be considered 
		// to compare with the present substring, i.e., next string
		// in suffix array
		int j = sa->sa[invSuff[i] + 1];
		
		// Directly start matching from k'th index as at-last 
		// k-1 characters will match
		while(i+k<sa->N && j+k<sa->N && sa->T[i+k]==sa->T[j+k]) k++;

		sa->lcp[invSuff[i]] = k; // lcp for the present suffix

		// Deleting the starting character from the string
		if(k>0) k--;
	}

	// Deallocate memory for invSuff
	free(invSuff);

	// Set true for constructed lcp array
	sa->constructedLcpArray = true;
}

/* END OF BUILDING LCP ARRAY */


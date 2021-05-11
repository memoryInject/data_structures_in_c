/*
 * Test driver program for Suffix Array Data Structure includes Least Common
 * Prefix(LCP) Array
 *
 * @author Mahesh MS, msmahesh@live.com
 * github: https://github.com/memoryInject
*/

#include "suffixArray.h"

// Test Driver Code
int main(int argc, char* argv[]){
	// Text = "banana"
	// suffix array for "banana" {5, 3, 1, 0, 4, 2}
	// least common prefix(lcp) array for "banana" {1, 3, 0, 0, 2, 0}
	char* text = "banana";
	int size = 6;
	struct SuffixArray* sa = suffixArrayInit(text, size);
	suffixArrayPrint(sa);

	suffixArrayClear(sa);
	return 0;
}


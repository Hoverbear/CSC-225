/* heapsort.c
   CSC 225 - Fall 2012
   Assignment 2 - Template for HeapSort

   This template includes some testing code to help verify the implementation.
   To interactively provide test inputs, run the program with
	./heapsort
   (assuming the executable name is 'heapsort')

   To conveniently test the algorithm with a large input, create a
   text file containing space-separated integer values and run the program with
	./heapsort file.txt
   where file.txt is replaced by the name of the text file.

   To compile your code (producing a binary called "heapsort"), use a command like
    gcc -o heapsort heapsort.c
   For marking purposes, your code must compile and run using the above command
   (without any special options) on one of the lab machines in ECS 242.

   B. Bird - 09/24/2012
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef MAX_VALUES
#define MAX_VALUES 1000000
#endif

// Swap code
void swap(int* array, int a, int b) {
	int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

// Recursive bubble down, from Algorithm 9 of lab notes 2
void recBubbleDown(int* array, int n, int i) {
	if ( (2*i) > n ){
		// Node is a leaf
		return;
	}
	int left = 2*i;
	int right = 2*i + 1;
	int max = left;
	if  (right <= n && array[max] < array[right])
		max = right;
	if (array[i] < array[max]) {
		// Swap
		swap(array, i, max);
		// Recurse
		recBubbleDown(array, n, max);
	}
}

// Recursive Heapify, from Algorithm 9 of lab notes 2
int* recHeapify(int* array, int n, int i) {
	if ((2*i) > n)
		// Node i is a leaf, and thus already a valid heap of size 1.
		return;
	// Recursively heapify the left tree
	recHeapify(array, n, 2*i);
	// Recursively heapify the right tree
	recHeapify(array, n, 2*i +1);
	// Bubble down the element at index i.
	recBubbleDown(array, n, i);
}

/* heapSort(inputArray,arrayLen)
	Sort the array inputArray, with length arrayLen, using an array-based heap sort algorithm.
	You may add additional functions if needed, but the entire program must be
	contained in this file. No dynamic memory allocation (malloc/calloc/realloc)
	is permitted or necessary. Do not use a linked data structure of any sort.
	Do not change the function signature (name/parameters).
*/
void heapSort(int* inputArray, int arrayLen){
    /* Create an array A which will contain the heap */
	/* A has size n+1 to allow 1-based indexing */
	int n = arrayLen;
	int A[n+1];
	// Initialize our indexer, since C is a bit odd.
	int i;


	/* Copy the array inputArray into A, with inputArray[i] being stored in A[i+1] */

	// Loop through to copy the array.
	A[0] = 0; // So we don't get any weird values.
	for (i=0; i < n; i++)
		A[i+1] = inputArray[i];

	/* Transform A into a max-heap using a 'bottom-up' algorithm (which must run in O(n) time). */
	/* One such algorithm is given in Part 2 of the Lab Notes. The recursive version
	   is algorithm 8 and the iterative version is algorithm 9. */
	recHeapify(A, n, 1);
	
	/* Perform a sequence of n 'remove-maximum' operations, storing the removed element at
	   each step in successively smaller indices of A (e.g. the first removed element
	   is stored in A[n], the second in A[n-1], etc.). Remember to use a 'bubble-down'
	   operation to restore the heap property after each removal. Pseudocode
	   for bubble down is given as part of algorithms 8 and 9 in Part 2 of the lab notes. */

	int end = n;
	while (end > 0) {
		swap(A, end, 1);
		end--;
		recBubbleDown(A, end, 1);
	}

	/* Copy the sorted values in A back into inputArray, with inputArray[i] getting
	   the value from A[i+1] */
	for (i=0; i < n; i++)
		inputArray[i] = A[i+1];

}

int main(int argc, char** argv){
	/* Code to test your implementation */
	/* You may modify this, but the contents of this function will be discarded
	   before marking (so do not put any of the heap sort implementation here) */

	int array[MAX_VALUES];
	int n = 0;
	int v,i;
	FILE* infile;

	if (argc > 1){
		//If a file argument was provided on the command line, read from the file
		infile = fopen(argv[1],"r");
		if (!infile){
			printf("Unable to open %s\n",argv[1]);
			return 0;
		}
		printf("Reading input values from %s.\n",argv[1]);
	}else{
		//Otherwise, read from standard input
		infile = stdin;
		printf("Enter up to %d positive integers to be sorted. ",MAX_VALUES);
		printf("Enter a negative value to end the list.\n");
	}

	while(n < MAX_VALUES && fscanf(infile,"%d",&v) > 0 && v >= 0)
		array[n++] = v;
	printf("Read %d values, sorting...\n",n);
	heapSort(array,n);
	//Don't print out the values if there are more than 100 of them
	if (n <= 100){
		printf("Sorted values:\n");
		for (i = 0; i < n; i++)
			printf("%d ",array[i]);
		printf("\n");
	}
	//Check whether the sort was successful
	int isSorted = 1;
	for (i = 0; i < n-1; i++)
		if (array[i] > array[i+1])
			isSorted = 0;
	printf("Array %s sorted.\n",isSorted? "is":"is not");
	return 0;
}

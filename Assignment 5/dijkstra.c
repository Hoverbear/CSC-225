/* dijkstra.c
   CSC 225 - Fall 2012
   Assignment 4 - Template for Dijkstra's Algorithm

   The assignment is to implement the dijkstra() function below, which takes a
   (positively) weighted adjacency matrix and the indices of two vertices and returns
   the length of the shortest path between them, or -1 if no path exists.
   Your implementation must run in O(m*log(n)) time in the worst case
   on a graph with n vertices and m edges.
   
   Do not change the name or parameters of the dijkstra() function.
   You may add other functions as necessary. Do not use global variables or
   goto statements.
   
   This template includes some testing code to help verify the implementation.
   The testing code reads a sequence of graphs and prints the length of the
   shortest path from vertex 0 to vertex n-1. Note that for marking purposes, your
   implementation will be expected to work with other pairs of vertices.
   Input graphs can be provided with standard input or read from a file.
   
   To provide test inputs with standard input, run the program with
	./dijkstra
   (assuming the executable name is 'dijkstra')
   To terminate the input, use Ctrl-D (which signals EOF).
   
   To read test inputs from a file (e.g. graphs.txt), run the program with
    ./dijkstra graphs.txt

   The input format for both methods is the same. Input consists
   of a series of graphs in the following format:
   
    <number of vertices>
	<adjacency matrix row 1>
	...
	<adjacency matrix row n>

   For example, a path on 3 vertices where one edge has weight 1 and the other
   edge has weight 2 would be represented by the following
   
    3
	0 1 0
	1 0 2
	0 2 0

   An input file can contain an unlimited number of graphs; each will be processed separately.
   
   B. Bird - 11/11/2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_VERTS
#define MAX_VERTS 256
#endif 
#ifndef MAX_VALUES
#define MAX_VALUES 1000000
#endif

/* dijkstra(G,n,i,j)
	Given a weighted adjacency matrix for graph G, return the length
	of the shortest (i,j)-path.

	For full marks, the implementation must run in O(m*log(n)) time in the worst
	case on a graph with n vertices and m edges.

	If G[i][j] == 0, there is no edge between vertex i and vertex j
	If G[i][j] > 1, there is an edge between i and j and the value of G[i][j] is its weight.
	No entry of G will be negative.

	n is the number of vertices in G (which may be less than MAX_VERTS).
*/
int dijkstra(int G[MAX_VERTS][MAX_VERTS], int n, int i, int j){
	int predecessor[MAX_VERTS], distance[MAX_VERTS];
	int visited[MAX_VERTS];
	int source;
	int numberOfVertices;
	
	distance[i] = 0;
	int index;
	for (index = 0; i < G.length; i++) {
		distance[index] = MAX_VALUES;
		
	}
	
}

/* HEAPSORT */
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
	int min = left;
	if  (right <= n && array[min] > array[right])
		min = right;
	if (array[i] > array[min]) {
		// Swap
		swap(array, i, min);
		// Recurse
		recBubbleDown(array, n, min);
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
	/* Transform A into a min-heap using a 'bottom-up' algorithm (which must run in O(n) time). */
	recHeapify(A, n, 1);
	/* Perform a sequence of n 'remove-minimum' operations, storing the removed element at
	   each step in successively smaller indices of A (e.g. the first removed element
	   is stored in A[n], the second in A[n-1], etc.).  */
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
	/* You may modify this, but nothing in this function will be marked */

	int i,j,valuesRead;

	int n = 0;
	int G[MAX_VERTS][MAX_VERTS];


	int graphNum = 0;
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
		printf("Reading input values from stdin.\n");
	}

	//Read graphs until EOF is encountered (or an error occurs)
	while(1){
		graphNum++;
		if(fscanf(infile,"%d",&n) < 1)
			break;
		printf("Reading graph %d\n",graphNum);
		valuesRead = 0;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				valuesRead += fscanf(infile,"%d",&G[i][j]);
		if (valuesRead < n*n){
			printf("Adjacency matrix for graph %d contains too few values.\n",graphNum);
			break;
		}
		int shortestPathLength = dijkstra(G,n,0,n-1);
		printf("Graph %d: Length of shortest (0,n-1)-path: %d\n",graphNum,shortestPathLength);
	}
	return 0;
}

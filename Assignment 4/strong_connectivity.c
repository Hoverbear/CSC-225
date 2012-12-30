/* strong_connectivity.c
   CSC 225 - Fall 2012
   Assignment 4 - Template for a Strong Connectivity Test

   The assignment is to implement the strongly_connected() function below, which 
   tests whether the provided graph is strongly connected. Section 4 of part 4
   of the lab notes contains some commentary on strong connectivity, as well as
   pseudocode for a strong connectivity test (although you are not required to 
   use the approach given in the notes). Your implementation must run in O(n^2)
   time on a graph with n vertices.
   
   Do not change the name or parameters of the strongly_connected() function.
   You may add other functions as necessary. Do not use global variables or
   goto statements.
   
   This template includes some testing code to help verify the implementation.
   Input graphs can be provided with standard input or read from a file.
   
   To provide test inputs with standard input, run the program with
	./strong_connectivity
   (assuming the executable name is 'strong_connectivity')
   To terminate the input, use Ctrl-D (which signals EOF).
   
   To read test inputs from a file (e.g. graphs.txt), run the program with
    ./strong_connectivity graphs.txt

   The input format for both methods is the same. Input consists
   of a series of graphs in the following format:
   
    <number of vertices>
	<adjacency matrix row 1>
	...
	<adjacency matrix row n>

   For example, a directed path on 3 vertices would be represented by the following
   
    3
	0 1 0
	0 0 1
	0 0 0

   Note that the above graph is not strongly connected.
   
   An input file can contain an unlimited number of graphs; each will be processed separately.
   
   B. Bird - 10/30/2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_VERTS
#define MAX_VERTS 256
#endif 

/* strongly_connected(G,n)
	Given an adjacency matrix for graph G, determine whether
	G is strongly connected.
	If G is strongly connected, return 1.
	Otherwise, return 0.

	For full marks, the implementation must run in O(n^2) time.

	If G[i][j] == 0, there is no edge between vertex i and vertex j
	If G[i][j] == 1, there is a directed edge from i to j.
	No entry of G will have a value other than 0 or 1.

	n is the number of vertices in G (which may be less than MAX_VERTS).
*/
int strongly_connected(int G[MAX_VERTS][MAX_VERTS], int n){

	/* ... Your code here ... */
	
	int covered[n]; // Initialize the array to 0 (false).
	int i; // For our loop, because C does weird stuff.
	for (i = 0; i < n; i++){ // Set all 'covered' to 0
		covered[i] = 0;
	}
	int u = 0; // Lets just take the first.
	
	// First go one way...
	int result = connectivityDFS(G, covered, u, n);
	if ( result < n ){
		return 0; // False
	}
	for (i = 0; i < n; i++){ // Set all 'covered' to 0
		covered[i] = 0;
	}
	
	// Then go the other!
	result = connectivityDFSTranspose(G, covered, u, n);
	if ( result < n ){
		return 0; // False
	}
	return 1; // True
}

/* In this function we address [row][column], as like normal. */
int connectivityDFS(int G[MAX_VERTS][MAX_VERTS], int covered[], int current, int n){
	int totalCovered = 1; // This is slightly misleading, as each recursive call has it's own 'total covered' but they all eventually add into the initial call, so it's fine.
	covered[current] = 1; // We're covering this one.
	int i; // For our loop, because C does weird stuff.
	for (i = 0; i < n; i++){ // Go over potential edges.
		if ( G[current][i] == 1 && covered[i] != 1 ){ // If it's an edge, and we haven't covered it already.
			totalCovered += connectivityDFS(G, covered, i, n);
		}
	}
	return totalCovered;
}

/* In this function we address [column][row], as like a transpose. */
int connectivityDFSTranspose(int G[MAX_VERTS][MAX_VERTS], int covered[], int current, int n){
	int totalCovered = 1; // This is slightly misleading, as each recursive call has it's own 'total covered' but they all eventually add into the initial call, so it's fine.
	covered[current] = 1; // We're covering this one.
	int i; // For our loop, because C does weird stuff.
	for (i = 0; i < n; i++){ // Go over potential edges.
		if ( G[i][current] == 1 && covered[i] != 1 ){ // If it's an edge, and we haven't covered it already.
			totalCovered += connectivityDFSTranspose(G, covered, i, n);
		}
	}
	return totalCovered;
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
			printf("	Adjacency matrix for graph %d contains too few values.\n",graphNum);
			break;
		}
		if (strongly_connected(G,n))
			printf("	Graph %d: Strongly Connected.\n",graphNum);
		else
			printf("	Graph %d: Not strongly connected.\n",graphNum);

	}
	return 0;
}

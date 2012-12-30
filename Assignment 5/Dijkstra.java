/* Dijkstra.java
	CSC 225 - Fall 2012
	Assignment 4 - Template for Dijkstra's Algorithm
	
	The assignment is to implement the dijkstra() method below, which takes a
	(positively) weighted adjacency matrix and the indices of two vertices and returns
	the length of the shortest path between them, or -1 if no path exists.
	Your implementation must run in O(m*log(n)) time in the worst case
	on a graph with n vertices and m edges.
	
	Do not change the name/parameters of the dijkstra() method and 
	do not rename the Dijkstra class. 
	Do not add the Dijkstra class to a java package (for marking purposes,
	your submission must run when the command given below is used).
	You may add other functions as necessary. Do not add any global variables.

	This template includes some testing code to help verify the implementation.
	The testing code reads a sequence of graphs and prints the length of the
	shortest path from vertex 0 to vertex n-1. Note that for marking purposes, your
	implementation will be expected to work with other pairs of vertices.
	Input graphs can be provided with standard input or read from a file.
	
	To provide test inputs with standard input, run the program with
	java Dijkstra
	To terminate the input, use Ctrl-D (which signals EOF).
	
	To read test inputs from a file (e.g. graphs.txt), run the program with
	 java Dijkstra graphs.txt
	
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
	
	Note that the above graph is not strongly connected.
	
	An input file can contain an unlimited number of graphs; each will be processed separately.
	
	B. Bird - 11/11/2012
*/

import java.util.Scanner;
import java.io.File;
import java.util.PriorityQueue;

class Data implements Comparable<Data> {
	public final int index;
	public final int priority;

	public Data(int index, int priority) {
		this.index = index;
		this.priority = priority;
	}

	@Override
	public int compareTo(Data other) {
		return Integer.valueOf(priority).compareTo(other.priority);
	}
	
	public boolean equals(Data other) {
		return priority == other.priority;
	}

	// also implement equals() and hashCode()
}

public class Dijkstra{
	/* dijkstra(G,n,i,j)
		Given a weighted adjacency matrix for graph G, return the length
		of the shortest (i,j)-path.
		
		For full marks, the implementation must run in O(m*log(n)) time in the worst
		case on a graph with n vertices and m edges.
		
		If G[i][j] == 0, there is no edge between vertex i and vertex j
		If G[i][j] > 1, there is an edge between i and j and the value of G[i][j] is its weight.
		No entry of G will be negative.
	*/
			
	static int MAX_VERTS = 50000;
	static int dijkstra(int[][] G, int i, int j){
		//Get the number of vertices in G
		int n = G.length;
		
		/* ... Your code here ... */
		int[] distance = new int[G.length];
		PriorityQueue<Data> PQ = new PriorityQueue<Data>();
		boolean[] inTree = new boolean[G.length];
		
		for (int index = 0; index < G.length; index++) {
			if (index == i) {
				distance[index] = 0;
			}
			else {
				distance[index] = Integer.MAX_VALUE;
				PQ.add(new Data(index,distance[index]));
				inTree[index] = true; 
			}
		}
		
		for (int index = 0; index < G.length; index++) { // for each edge (v,z) do
			if (G[i][index] != 0) { // There is an edge
				if (distance[i] + G[i][index] < distance[index]) { // if D[v] + w((v,z)) < D[z] then 
					int oldIndex = distance[index];
					distance[index] = distance[i] + G[i][index]; // D[z] ← D[v] + w((v,z))  
					PQ.remove(new Data(index, oldIndex));
					PQ.add(new Data(index, distance[index])); // update PQ wrt D[z] 
				}
			}
		}
		
			
		while (PQ.peek() != null) { // If PQ isn't empty
			Data vertex = PQ.poll(); // RemoveMin
			for (int index = 0; index < G.length; index++) { // for each edge (u,z) with z ∈ PQ do
				if (G[vertex.index][index] != 0 && inTree[index] == true) { // z ∈ PQ
					if (distance[vertex.index] + G[vertex.index][index] < distance[index]) { // if D[v] + w((v,z)) < D[z] then 
						int oldIndex = distance[index];
						distance[index] = distance[vertex.index] + G[vertex.index][index]; // D[z] ← D[v] + w((v,z)) 
						PQ.remove(new Data(index, oldIndex));
						PQ.add(new Data(index, distance[index])); // update PQ wrt D[z] 
					}
				}
			
			}
		}
		if (distance[j] == Integer.MAX_VALUE || distance[j] < 0) {
			return -1;
		}
		else {
			return distance[j];
		}
		
		
	}

	public static void main(String[] args){
		/* Code to test your implementation */
		/* You may modify this, but nothing in this function will be marked */

		int graphNum = 0;
		Scanner s;

		if (args.length > 0){
			//If a file argument was provided on the command line, read from the file
			try{
				s = new Scanner(new File(args[0]));
			} catch(java.io.FileNotFoundException e){
				System.out.printf("Unable to open %s\n",args[0]);
				return;
			}
			System.out.printf("Reading input values from %s.\n",args[0]);
		}else{
			//Otherwise, read from standard input
			s = new Scanner(System.in);
			System.out.printf("Reading input values from stdin.\n");
		}
		
		//Read graphs until EOF is encountered (or an error occurs)
		while(true){
			graphNum++;
			if(!s.hasNextInt())
				break;
			System.out.printf("Reading graph %d\n",graphNum);
			int n = s.nextInt();
			int[][] G = new int[n][n];
			int valuesRead = 0;
			for (int i = 0; i < n && s.hasNextInt(); i++){
				G[i] = new int[n];
				for (int j = 0; j < n && s.hasNextInt(); j++){
					G[i][j] = s.nextInt();
					valuesRead++;
				}
			}
			if (valuesRead < n*n){
				System.out.printf("Adjacency matrix for graph %d contains too few values.\n",graphNum);
				break;
			}
			int shortestPathLength = dijkstra(G,0,n-1);
			System.out.printf("Graph %d: Length of shortest (0,n-1)-path: %d\n",graphNum,shortestPathLength);
		}
	}

}
// Compile : clang adjacencymatrix.c -o adjacencymatrix 
//           ^ Note: You may get a few warnings for passing pointers around, this is okay for this lab.
// Run with: ./adjacencymatrix
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 5
#define COLUMNS 5

// These defines do a text replacement
// everytime the string 'ROWS' and 'COLUMNS'
// are found in this specific source file.
// You can play with these values.

/*  ============= Tutorial on Graph format ============
    You are given a randomly generated graph that looks 
    of the form:

    0 0 1 1 1
    1 0 0 1 1
    0 1 0 1 1
    1 0 0 0 0
    1 0 1 1 0

    You can think of the graph with labels for each of
    the nodes (sometimes called vertices) more clearly below:

               0 1 2 3 4
               ---------  
    node 0:    0 0 1 1 1
    node 1:    1 0 0 1 1
    node 2:    0 1 0 1 1
    node 3:    1 0 0 0 0
    node 4:    1 0 1 1 0

    A '1' represents a connection to a node, and a 0
    means it is not connected.

               0 1 2 3 4
               ---------  
    node 0:    0 0 1 1 1
    node 1:    1 0 0 1 1
    node 2:    0 1 0 1 1
    node 3:    1 0 0 0 0
    node 4:    1 0 1 1 0

    In the above, '0' is connected to 2, 3, and 4.
    That means node 0 has directed-edges out 
    to nodes  2,3,and 4. In other words, 
    the edge-list for node 0 is:
    0->2, 0->3, 0->4
    
    The number of connections a node has out is its 'out-degree'
    The number of connections a node has in are it's 'in-degree'
*/



// This function generates a random graph
// Note: For the purpose of this lab,
//       we do not seed the random number generator
//       so we can generate the same graph over
//       and over again.
void generateGraph(int** g){
    // Uncomment the line below if you want
    // to generate a random graph each time.
    // srand(time(NULL));  
    int i,j;
    for(i=0; i < ROWS; i++){
        for(j=0; j < COLUMNS; j++){
            if(i==j){
                g[i][j] = 0; // Why do we have this condition? to make sure each vertex has no cycle with itself
            }else{
                g[i][j] = rand() % 2;
            }
        }
    }
}

// This function will print out the adjacency
// matrix for a graph.
void printGraph(int** g){ 
    int i,j;
    for(i=0; i < ROWS; i++){
        for(j=0; j < COLUMNS; j++){
            printf("%d ",g[i][j]);
        }
        printf("\n");
    }
}

// Compute 'in-degree' of a node
// For a given node 'n' in an adjacency matrix,
// compute the in-degree.
int nodeInDegree(int** g, int node){
    // TODO
    int i;
    int inDegreeNum = 0;
    for(i=0; i< ROWS; i++){
	if (g[i][node] == 1) {
		inDegreeNum += 1;
	}
    }	
    return inDegreeNum;
}

// Compute 'out-degree' of a node
// For a given node 'n' in an adjacency matrix,
// compute the out-degree.
int nodeOutDegree(int** g, int node){
    // TODO
    int i;
    int outDegreeNum = 0;
    for(i=0; i< COLUMNS; i++){
	if (g[node][i] == 1) {
		outDegreeNum += 1;
	}
    }	
    return outDegreeNum;
}


// Figure out if two nodes are connected
// Returns a 1 if node1 is connected to node 2
int isConnected(int** g, int node1, int node2){
    // TODO
    if (g[node1][node2] == 1) {
	return 1;
    }
    return 0;
}


// free Graph
void freeGraph(int** g) {
        int i=0;
        for (i = 0;i < ROWS; i++) {
                free(g[i]);
        }

        free(g);
}


int main(){
    int** g_testgraph = (int**)malloc(sizeof(int*)*ROWS);

    int i=0;
    for (i=0; i < ROWS; ++i) {
        g_testgraph[i] = (int*)malloc(sizeof(int)*COLUMNS);
    } 
    // Generate a random graph
    generateGraph(g_testgraph);
    // Print out the graph
    printGraph(g_testgraph);
    printf("\n");
    // Print out the nodeInDegree of each of the
    // five nodes
    for(i =0; i < COLUMNS; ++i){
        printf("node %d in-degree= %d\n",i,nodeInDegree(g_testgraph,i));
    }
    printf("\n");

    // Print out the nodeInDegree of each of the
    // five nodes
    for(i =0; i < COLUMNS; ++i){
        printf("node %d out-degree= %d\n",i,nodeOutDegree(g_testgraph,i));
    }
    printf("\n");

    // Check which nodes '0' is connected to
    printf("Node 0 connections:");

    int j;
    int has_connect = 0;
    for(j =0; j < COLUMNS; ++j){
        if (isConnected(g_testgraph,0,j)) {
                has_connect = 1;
        	printf("node%d ", j);
	}
    }
    printf("\n");
    // if node has no connections, return nobody
    if (!has_connect) {
	printf("nobody\n");
    }
    // free graph
    freeGraph(g_testgraph);

    return 0;
}

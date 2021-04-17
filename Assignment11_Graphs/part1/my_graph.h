// =================== Support Code =================
// Graph.
//
//
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
}graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
}graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= (graph_t*)malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t* g, int value){
	if (g == NULL) return NULL;

	node_t* iter = g->nodes->head;
	while (iter != NULL){
		graph_node_t* g_node = iter->data;
		if (g_node->data == value) {
			return g_node;
		}
		iter = iter->next;
	}	

       	return NULL;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t* create_graph_node(int value){
    graph_node_t* graph_node = (graph_node_t*)malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return 0;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if the node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    if ( g == NULL ) return NULL;

    graph_node_t* g_node = find_node(g, value);
    // the node doesn't exist
    if (g_node == NULL) return NULL;

    return g_node->inNeighbors;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    if ( g == NULL ) return -1;

    graph_node_t* g_node = find_node(g, value);
    // the node doesn't exist
    if (g_node == NULL) return -1;

    return g_node->inNeighbors->count;
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    if ( g == NULL ) return NULL;

    graph_node_t* g_node = find_node(g, value);
    // the node doesn't exist
    if (g_node == NULL) return NULL;

    return g_node->outNeighbors;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    if ( g == NULL ) return -1;

    graph_node_t* g_node = find_node(g, value);
    // the node doesn't exist
    if (g_node == NULL) return -1;

    return g_node->outNeighbors->count;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
    if ( g == NULL ) return -1;

    graph_node_t* remove_node = find_node(g, value);
    // if the node doesn't exist
    if (remove_node == NULL) return 0;
   
    dll_t* outNeighbors = getOutNeighbors(g, value);
    dll_t* inNeighbors = getInNeighbors(g, value);
   
    // remove remove_node from all its outNeighbors 
    node_t* iter_out = remove_node->outNeighbors->head;    
    while(iter_out != NULL) {
	graph_node_t* g_node = iter_out->data;
    	dll_remove_node(g_node->inNeighbors, remove_node);
        g->numEdges--;
        iter_out = iter_out->next;
    }

    // remove remove_node from all its inNeighbors 
    node_t* iter_in = remove_node->inNeighbors->head; 
    while(iter_in != NULL) {
 	graph_node_t* g_node = iter_in->data;
    	dll_remove_node(g_node->outNeighbors, remove_node);
        g->numEdges--;
	iter_in = iter_in->next;
    }
    // free in and out neighbors of remove_node 
    free_dll(remove_node->inNeighbors);
    free_dll(remove_node->outNeighbors);
    // remove remove_node from graph nodes 
    dll_remove_node(g->nodes, remove_node);
    free(remove_node);
    g->numNodes--;

    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    if ( g == NULL ) return -1;

    graph_node_t* source_node = find_node(g, source);
    graph_node_t* des_node = find_node(g, destination);

    if (source_node == NULL || des_node == NULL) return 0;

    node_t* iter = source_node->outNeighbors->head;
    while (iter != NULL){
    	graph_node_t* g_node = iter->data;
    	if (g_node->data == destination) {
    		return 1;
    	}
    	iter = iter->next;
    }	
    return 0;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.
    if ( g == NULL ) return -1;

    graph_node_t* source_node = find_node(g, source);
    graph_node_t* des_node = find_node(g, destination);
    // the source or destination nodes don't exist
    if (source_node == NULL || des_node == NULL) return 0;

    // the edge already exists
    if (contains_edge(g, source, destination)) return 0;
   
    dll_push_back(source_node->outNeighbors, des_node);
    dll_push_back(des_node->inNeighbors, source_node);
    g->numEdges++; 

    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
    if ( g == NULL ) return -1;

    graph_node_t* source_node = find_node(g, source);
    graph_node_t* des_node = find_node(g, destination);
    // the source or destination nodes don't exist
    if (source_node == NULL || des_node == NULL) return 0;

    // the edge doesn't exists
    if (!contains_edge(g, source, destination)) return 0;
        
    int desPosInSourceOutNeig = dll_get_pos(source_node->outNeighbors, des_node);
    int sourcePosInDesInNeig = dll_get_pos(des_node->inNeighbors, source_node);

    dll_remove_node(source_node->outNeighbors, des_node);
    dll_remove_node(des_node->inNeighbors, source_node);
    g->numEdges--;

    return 1;
}


// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if (g == NULL) {
	return -1;
    }
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    if (g == NULL) return -1;

    return g->numEdges;
}
// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    if (g == NULL) return;
    
	node_t* iter = g->nodes->head;
	while (iter != NULL){
		graph_node_t* g_node = iter->data;
		free_dll(g_node->inNeighbors);
		free_dll(g_node->outNeighbors);
                free(g_node);
		iter = iter->next;
	}	

        free_dll(g->nodes);
        free(g);
}

#endif

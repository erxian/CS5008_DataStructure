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
    if (myGraph == NULL) return NULL;

    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t* g, int value){
	if (g == NULL) return NULL;

	//node_t* iter = g->nodes->head;
	//while (iter != NULL){
	//	graph_node_t* g_node = iter->data;
	//	if (g_node->data == value) {
	//		return g_node;
	//	}
	//	iter = iter->next;
	//}	
	int i;
        for (i=0; i < g->numNodes; i++) {
		graph_node_t* g_node =  dll_get(g->nodes, i);
		if (g_node->data == value) {
			return g_node;
		}
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
    
    int success;
    success = dll_push_back(g->nodes, newNode);
    // if push success ++ node number 
    if (success) g->numNodes++;
    
    return success;
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
    // fine del_node according to its value
    graph_node_t* del_node = find_node(g, value);
    // if the node doesn't exist
    if (del_node == NULL) return 0;
   
    int outNeigNum = getNumOutNeighbors(g, value);
    dll_t* outNeighbors = getOutNeighbors(g, value);
    
    int inNeigNum = getNumInNeighbors(g, value);
    dll_t* inNeighbors = getInNeighbors(g, value);
   
    // remove del_node from all its outNeighbors 
    //node_t* iter_out = del_node->outNeighbors->head;    
    //while(iter_out != NULL) {
    //    graph_node_t* g_node = iter_out->data;
    //	dll_remove_node(g_node->inNeighbors, del_node);
    //    g->numEdges--;
    //    iter_out = iter_out->next;
    //}
    int i, j;
    for (i=0; i < outNeigNum; i++) {
	graph_node_t* out_neig_node = dll_get(outNeighbors, i);  // get outNeighbor node
        int in_Neig_Num = getNumInNeighbors(g, out_neig_node->data);  // get the inNeighborNum of this outNeighbor node
        dll_t* in_Neighbors = getInNeighbors(g, out_neig_node->data);  // get inNeighbors of this outNeighbor node
	for(j=0; j <  in_Neig_Num; j++) {
		graph_node_t* g_node = dll_get(in_Neighbors, j);  // get inNeighbors of this outNeighbor node
		if (g_node == del_node) {
			// validate if remove success
			int success = dll_remove(in_Neighbors, j);
			if (success) {
 				g->numEdges--;
			} else {
				return 0;
			}
		}
	}
    } 
		

    // remove del_node from all its inNeighbors 
    //node_t* iter_in = del_node->inNeighbors->head; 
    //while(iter_in != NULL) {
    //    graph_node_t* g_node = iter_in->data;
    //	dll_remove_node(g_node->outNeighbors, del_node);
    //    g->numEdges--;
    //    iter_in = iter_in->next;
    //}

    for (i=0; i < inNeigNum; i++) {
	graph_node_t* in_neig_node = dll_get(inNeighbors, i);
        int out_Neig_Num = getNumOutNeighbors(g, in_neig_node->data);
        dll_t* out_Neighbors = getOutNeighbors(g, in_neig_node->data);
	for(j=0; j <  out_Neig_Num; j++) {
		graph_node_t* g_node = dll_get(out_Neighbors, j);
		if (g_node == del_node) {
			dll_remove(out_Neighbors, j);
 			g->numEdges--;
		}
	}
    } 
		

    // free in and out neighbors of del_node 
    free_dll(del_node->inNeighbors);
    free_dll(del_node->outNeighbors);
    // remove remove_node from graph nodes 
    //dll_remove_node(g->nodes, del_node);
    for (i=0; i < g->numNodes; i++) {
	graph_node_t* g_node = dll_get(g->nodes, i);
	if (g_node == del_node) {
		dll_remove(g->nodes, i);
		g->numNodes--;
	}	
    }	

    free(del_node);

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

    //node_t* iter = source_node->outNeighbors->head;
    //while (iter != NULL){
    //	graph_node_t* g_node = iter->data;
    //	if (g_node->data == destination) {
    //		return 1;
    //	}
    //	iter = iter->next;
    //}	
    
    dll_t* out_Neighbors = getOutNeighbors(g, source);
    dll_t* in_Neighbors = getInNeighbors(g, destination);
    if (contains_node(out_Neighbors, des_node) &&
	contains_node(in_Neighbors, source_node)) {
		return 1;
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
  
    int push_des_success;
    int push_source_success; 
    push_des_success = dll_push_back(source_node->outNeighbors, des_node);
    push_source_success = dll_push_back(des_node->inNeighbors, source_node);
    // push des to source_out_neig success and push source ot des_in_neig success 
    if (push_des_success && push_source_success) {
	g->numEdges++; 
    	return 1;
    }
    return 0;
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
    
        
    //dll_remove_node(source_node->outNeighbors, des_node);
    //dll_remove_node(des_node->inNeighbors, source_node);
    int outNeigNum = getNumOutNeighbors(g, source);
    dll_t* outNeighbors = getOutNeighbors(g, source); 

    int i;
    for (i=0; i < outNeigNum; i++) {
	graph_node_t* g_node = dll_get(outNeighbors, i);
	if (g_node == des_node) {
		dll_remove(outNeighbors, i);
	}
    }


    int inNeigNum = getNumOutNeighbors(g, destination);
    dll_t* inNeighbors = getInNeighbors(g, destination); 

    int j;
    for (j=0; j < inNeigNum; j++) {
	graph_node_t* g_node = dll_get(inNeighbors, j);
	if (g_node == source_node) {
		dll_remove(outNeighbors, j);
	}
    }

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

// print graph nodes and its neighbors
void print_graph(graph_t* g) {
	if (g == NULL) return;
	node_t* iter = g->nodes->head;
	while (iter != NULL){
		graph_node_t* g_node = iter->data;
		printf("In neighbors are: ");
		node_t* iter_in = g_node->inNeighbors->head;
		while (iter_in != NULL) {
			graph_node_t* tmp_in_node = iter_in->data;
			printf("%d ", tmp_in_node->data);
			iter_in = iter_in->next;
		}

		printf(", node is %d, ", g_node->data);

		printf("Out neighbors are: ");
		node_t* iter_out = g_node->outNeighbors->head;
		while (iter_out != NULL) {
			graph_node_t* tmp_out_node = iter_out->data;
			printf("%d ", tmp_out_node->data);
			iter_out = iter_out->next;
		}
		printf("\n");
		iter = iter->next;	
	}	
}


#endif

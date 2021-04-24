// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int main(int argc, const char * argv[]) {
    graph_t * graph = create_graph();
    // add node 1, 2, 3, 4
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);
    graph_add_node(graph, 5);
    graph_add_node(graph, 6);
    graph_add_node(graph, 7);
    graph_add_node(graph, 8);
    graph_add_node(graph, 9);
    graph_add_node(graph, 10);
    graph_add_node(graph, 11);

    // add edges
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 2, 4);
    graph_add_edge(graph, 4, 5);
    graph_add_edge(graph, 2, 6);
    graph_add_edge(graph, 6, 7);
    graph_add_edge(graph, 7, 8);
    graph_add_edge(graph, 8, 6);
    graph_add_edge(graph, 8, 9);
    graph_add_edge(graph, 9, 10);
    graph_add_edge(graph, 8, 11);
    graph_add_edge(graph, 11, 1);

    printf("\n");
   
    //printf("graph node number is %d, edges is %d\n", graph->numNodes, graph->numEdges);
    //print_graph(graph);
    //graph_remove_node(graph, 8);
    //
    //printf("\n");
    //printf("graph node number is %d, edges is %d\n", graph->numNodes, graph->numEdges);
    //print_graph(graph);
    
    int node1 = 8;
    int node2 = 7;
    printf("node%d to node%d is reachable %d\n", node1, node2, is_reachable(graph, node1, node2));
    printf("\n");

    printf("node%d to node: %d\n", node1, node2);
    print_path(graph, node1, node2);

    printf("\n");
    has_cycle(graph);
    free_graph(graph);

    return 0;
}

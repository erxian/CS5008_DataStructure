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
    //int node = 5; //graph_node_t* target_node = find_node(graph, node);
    //if (target_node == NULL) {
    //    printf("no such node\n");
    //} else {
    //    printf("node data is %d\n", target_node->data);
    //} 
    // add edge 1 to 2, 3, 4; 2 to 3, 4; 3 to 4 
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 1, 3);
    graph_add_edge(graph, 1, 4);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 2, 4);
    graph_add_edge(graph, 3, 4);
    printf("contains edge 1 to 4 = %d\n", contains_edge(graph, 1, 4));
    print_graph(graph);
    printf("before total nodes = %d\n", graph_num_nodes(graph));
    printf("before total edges = %d\n", graph_num_edges(graph));

    //printf("find 1 in graph, its value is %d\n", find_node(graph, 1)->data);
    //printf("from node%d to node%d contains edge %d\n", 2, 4, contains_edge(graph, 2, 4));
    //printf("node%d in neighbors nums is %d\n", node, getNumInNeighbors(graph, node));
    //printf("node%d out neighbors nums is %d\n", 1, getNumOutNeighbors(graph, 1));
    //graph_node_t* target_node = find_node(graph, node);

    int node = 2;
    graph_remove_node(graph, node);

    printf("\n");
    print_graph(graph);
    printf("after total nodes = %d\n", graph_num_nodes(graph));
    printf("after total edges = %d\n", graph_num_edges(graph));

    //printf("node%d positon is %d\n", node, dll_get_pos(getOutNeighbors(graph, 1), target_node));
    //graph_remove_edge(graph, 1, 3);

    //printf("node%d in neighbors nums is %d\n", node, getNumInNeighbors(graph, node));
    //printf("node%d out neighbors nums is %d\n", 1, getNumOutNeighbors(graph, 1));
    //print_graph(graph);
    free_graph(graph);

    return 0;
}

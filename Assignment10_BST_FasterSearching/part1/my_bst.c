// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>


bstnode_t* makeNode(int data) {
	bstnode_t* bstNode = malloc(sizeof(bstnode_t));
    	if (bstNode == NULL) {
		return NULL;
   	 }
    	bstNode->data = data;
    	bstNode->leftChild = NULL;
    	bstNode->rightChild = NULL;

	return bstNode;
}	 


// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    // Modify the body of this function as needed.
    bst_t* myBST = malloc(sizeof(bst_t));; 
    if (myBST == NULL) {
	return NULL;
    }
    myBST->size = 0;
    myBST->root = NULL;

    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
	if (t->size == 0) {
		return 1;
	}
    	return 0;
}

// recursively add node to tree
int addHelper(bstnode_t* node, bstnode_t* newNode) {
	if (newNode->data <= node->data) {
		if (node->leftChild == NULL) {
			node->leftChild = newNode;
		} else {
			addHelper(node->leftChild, newNode);
		}
	} else if (newNode->data > node->data) {
		if (node->rightChild == NULL) {
			node->rightChild = newNode;
		} else {
			addHelper(node->rightChild, newNode);
		}
	}
	return 0;
}


// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){
	if (t == NULL) {
		return 0;
	}

	bstnode_t* newNode = makeNode(item);	
	if (newNode == NULL) {
		return -1;
	}
	// if root is NULL
	if (t->root == NULL) {
		t->root = newNode;
		t->size += 1;
		return 1;
	}
	// if root is not NULL, add newNode to tree
	addHelper(t->root, newNode);
	t->size += 1;

	return 1;
}

// recursively print node in ascending order
void printAscending(bstnode_t* node) {
	if (node == NULL) {
		return;
	}
	printAscending(node->leftChild);
	printf("%d ", node->data);
	printAscending(node->rightChild);
}

// recursively print node in descending order
void printDescending(bstnode_t* node) {
	if (node == NULL) {
		return;
	}
	printDescending(node->rightChild);
	printf("%d ", node->data);
	printDescending(node->leftChild);
}


// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// For NULL tree -- print "(NULL)".
// It should run in O(n) time.
void bst_print(bst_t *t, int order){
    if(NULL == t){
        printf("(NULL)");
    }else{
	if (order == 0) {
		printAscending(t->root);
	} else {
		printDescending(t->root);
	}
    }
}

// resursively add all nodes of the tree
int sumHelper(bstnode_t* node) {
	if (node == NULL) {
		return 0;
	}
	return node->data + sumHelper(node->leftChild) + sumHelper(node->rightChild);
}


// Returns the sum of all the nodes in the bst. 
// exits the program for a NULL tree. 
// It should run in O(n) time.
int bst_sum(bst_t *t){
	if (NULL == t) {
		exit(1);
	}
	
	int sum;
	sum = sumHelper(t->root);
  	return sum;
}

// recursively compare value with node
int find(bstnode_t* node, int value) {
	// touch the bottom of the tree
	// value can is not in the tree
	if (node == NULL) {
		return 0;
	}
	// find the value
	if (node->data == value) {
		return 1;
	}
	
	// if value larger than node data
	// keep finding the right child of the node	
	// otherwise finding the left child of the node
	if (node->data < value) {
		return find(node->rightChild, value);
	} else {
		return find(node->leftChild, value);
	}
} 

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree it exists the program. 
// It should run in O(log(n)) time.
int bst_find(bst_t* t, int value){
	if (t == NULL) {
		exit(1);
	}

	int result;
	result = find(t->root, value); 

	return result;	
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
	if (t == NULL) {
		exit(1);
	}
    	return t->size;
}

void freeNode(bstnode_t* node) {
	if (node == NULL) {
		return;
	}
	freeNode(node->leftChild);
	freeNode(node->rightChild);
	free(node);
}


// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){
	freeNode(t->root);
}


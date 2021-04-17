// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

#include <stdlib.h>
// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node{
    void* data;
    struct node* next;
    struct node* previous;
}node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL{
    int count;        // count keeps track of how many items are in the DLL.
    node_t* head;        // head points to the first node in our DLL.
    node_t* tail;          //tail points to the last node in our DLL.
}dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    // Modify the body of this function as needed.
    dll_t* myDLL= (dll_t*)malloc(sizeof(dll_t));

    if (myDLL == NULL) {
	return NULL;
    }
    myDLL->count =0;
    myDLL->head = NULL;
    myDLL->tail = NULL;
    return myDLL;
}

// DLL Size
// Queries the current size of a DLL
// Returns -1 if the DLL is NULL.
int dll_size(dll_t* t){
   	if ( t == NULL){
		return -1;
	} 
        return t->count; // Note: This line is a 'filler' so the code compiles.
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
// Returns -1 if the dll is NULL.
int dll_empty(dll_t* l){
	if ( dll_size(l) == 0 ){
		return 1;
	}
    	return 0;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
	if ( l == NULL){
		return -1;
	}
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if ( newNode == NULL ){
		return 0;
	}
	newNode->data = item;
	newNode->next = l->head;
	newNode->previous = NULL;
	if (l->head == NULL){
		l->head = l->tail = newNode;	
	} else {
		l->head->previous = newNode;
		l->head = newNode;
	}
	l->count++;
	return 1;	
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
	if ( l == NULL){	
		return -1; 
	}
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if ( newNode == NULL ){
		return 0;
	}
	newNode->data = item;
	newNode->next = NULL;
	newNode->previous = l->tail;
	if ( l->tail == NULL){
		l->tail = l->head = newNode;
	} else {
		l->tail->next = newNode;
		l->tail = newNode;
	}
	l->count++;
	return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* t){
	if ( t == NULL ){
		//return -1;
		return NULL;
	}
	//check if stack is empty
	if ( dll_empty(t)){
		//return 0; // Note: This line is a 'filler' so the code compiles.
		return NULL;
	}
	if ( t->head == NULL ){
		//return -1;
		return NULL;
	}
	//int item = t->head->data;
	void* item = t->head->data;
	if ( t->head == t->tail ){
		free(t->head);
		t->head = t->tail = NULL;
	} else {
		node_t* tmpNode;
		tmpNode = t->head->next;
		tmpNode->previous = NULL;
		free(t->head);
		t->head = tmpNode;
	}
	t->count--;
	return item;
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* t){
	if ( t == NULL ){
		//return -1;
		return NULL;
	}
	//check if stack is empty
	if ( dll_empty(t)){
		//return 0; // Note: This line is a 'filler' so the code compiles.
		return NULL;
	}
	if ( t->tail == NULL ){
		//return -1;
		return NULL;
	}

	//int item = t->tail->data;
	void* item = t->tail->data;
	
	if ( t->tail == t->head){
		free(t->tail);
		t->tail = t->head = NULL;
	} else { 
		node_t* tmpNode;
		tmpNode = t->tail->previous;
		tmpNode->next = NULL;
		free(t->tail);
		t->tail = tmpNode;
	}
	t->count--;
	return item;
}

// Inserts a new node before the node at the specified position.
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
// Returns -1 if the list is NULL
int dll_insert(dll_t* l, int pos, void* item){
	if ( l == NULL){
		return -1;
	}
	// if pos is negative or past the size of the list
	if ( pos > dll_size(l) || pos < 0){
		return 0;
	}

	int success = 1;	
	// inserting at the size pos
	if ( pos == dll_size(l)){
		success = dll_push_back(l, item);
	// insert at 0 pos
	} else if ( pos == 0 ){
		success = dll_push_front(l, item);
	} else {
		node_t* currentNode = l->head;
		int i;
		for(i=0; i < pos; i++){
			currentNode = currentNode->next;
		}
		node_t* preNode = currentNode->previous;

		node_t* newNode = (node_t*)malloc(sizeof(node_t));
		if ( newNode == NULL ){
			return -1;
		}	
		newNode->data = item;
		newNode->next = currentNode;
		newNode->previous = preNode;

		preNode->next = newNode;
		currentNode->previous = newNode;
		l->count++;
	}
	return success;        
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
//  (does not remove the item)
// Retruns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Returns -1 if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
	if ( l == NULL ){		
		//return -1; // Note: This line is a 'filler' so the code compiles.
		return NULL;
	}

	// if pos is negative or past the size of the list
	if ( pos > dll_size(l) - 1 || pos < 0){
		//return 0;
		return NULL;
	}
	if ( pos == 0 ){
		return l->head->data;
	} else if ( pos == dll_size(l) - 1 ){
		return l->tail->data;
	} else {	
		node_t* currentNode = l->head;
		int i;
		for( i=0; i < pos; i++){
			currentNode = currentNode->next;
		}
		return currentNode->data;
	}
}


// Removes the item at position pos starting at 0 ( 0 being the first item )
// Retruns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Returns NULL if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
	if ( l == NULL ){		
		//return -1; // Note: This line is a 'filler' so the code compiles.
		return NULL;
	}

	// if pos is negative or past the size of the list
	if ( pos > dll_size(l) - 1 || pos < 0){
		//return 0;
		return NULL;
	}

	if ( pos == 0 ){
		dll_pop_front(l);	
	} else if ( pos == dll_size(l) - 1 ){
		dll_pop_back(l);
	} else {	
		node_t* currentNode = l->head;
		int i;
		for( i=0; i < pos; i++){
			currentNode = currentNode->next;
		}
		node_t* preNode = currentNode->previous;
		node_t* nextNode = currentNode->next;
		preNode->next = nextNode;
		nextNode->previous = preNode;
		free(currentNode);
		l->count--;
	}

	//return 1;
	return NULL;
}

// Returns 1 on success
// Returns 0 on failure ( or if the nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_node(dll_t* l, void* item) {
	if (l == NULL) return -1;

	node_t* iter = l->head;
	while (iter != NULL) {
		if (iter->data == item) {
			return 1;
		}
		iter = iter->next;
	}	
	return 0;
}

// Removes the node with value item
// Retruns NULL on failure (e.g. del node not in dll or node is null
// Returns NULL if the list is NULL
void* dll_remove_node(dll_t* l, void* item) {
	if (l == NULL) return NULL;
       	// if node not in dll 
	if (!contains_node(l, item)) return NULL;

        // If node to be deleted is head node
	if (l->head->data == item) {
		dll_pop_front(l);	
	// If node to be deleted is head node
	} else if (l->tail->data == item) {
		dll_pop_back(l);
	} else {
		node_t* iter = l->head;
		while (iter != NULL && iter->data != item) {
			iter = iter->next;
		}	
		// find node iter with data item
		iter->previous->next = iter->next;
		iter->next->previous = iter->previous;	
		free(iter);
		l->count--;
	}	
	return NULL;
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
	if ( t == NULL){
		return;
	}
	node_t* nextNode;
	while ( t->head != NULL){
		nextNode = t->head->next;
		free(t->head);
		t->head = nextNode;
	}
	free(t);
}

// Helper function
void printDll(dll_t* l){
	node_t* itr = l->head;
	while( itr != NULL){
		printf("%d ", *((int*)itr->data));
		itr = itr->next;
	}
	printf("\n");
}

#endif


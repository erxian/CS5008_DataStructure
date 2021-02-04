// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// Create your node_t type here
typedef struct node{
	int year;
	int wins;
	struct node* next;
}node_t;


// Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.


node_t* makeNode(int year, int wins, struct node* next){
	node_t* p_aNode = (node_t*)malloc(sizeof(node_t));
	p_aNode->year = year;
	p_aNode->wins = wins;
	p_aNode->next = next;
	return p_aNode;
}


node_t* create_list(){
	node_t* year2014 = makeNode(2014, 71, NULL);
	node_t* year2015 = makeNode(2015, 78, year2014);
	node_t* year2016 = makeNode(2016, 93, year2015);
	node_t* year2017 = makeNode(2017, 93, year2016);
	node_t* year2018 = makeNode(2018, 108, year2017);

	return year2018;
}


void printList(node_t* iterator){
	while(iterator != NULL){
		printf("%d, %d wins\n", iterator->year, iterator->wins);
		iterator = iterator->next;
	}
}


void freeList(node_t* iterator){
	node_t* nextNode;
	while(iterator != NULL){
		nextNode = iterator->next;
		free(iterator);
		iterator = nextNode;
	}
}


int main(){
	node_t* redsox = NULL;

	redsox = create_list();

	node_t* iterator = redsox;

	printList(iterator);

	freeList(iterator);

	return 0;
}

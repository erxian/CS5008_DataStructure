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


node_t* create_list(){
	node_t* year2018 = malloc(sizeof(node_t));
	node_t* year2017 = malloc(sizeof(node_t));
	node_t* year2016 = malloc(sizeof(node_t));
	node_t* year2015 = malloc(sizeof(node_t));
	node_t* year2014 = malloc(sizeof(node_t));



	year2018->year = 2018;
	year2017->year = 2017;
	year2016->year = 2016;
	year2015->year = 2015;
	year2014->year = 2014;

	year2018->wins = 108;
	year2017->wins = 93;
	year2016->wins = 93;
	year2015->wins = 78;
	year2014->wins = 71;

	year2018->next = year2017;
	year2017->next = year2016;
	year2016->next = year2015;
	year2015->next = year2014;
	year2014->next = NULL;

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

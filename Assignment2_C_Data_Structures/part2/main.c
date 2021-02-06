// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "mystack.h"
// Note that we are locating this file
// within the same directory, so we use quotations 
// and provide the path to this file which is within
// our current directory.


// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.
void unitTest1(){
	stack_t* test1 = create_stack(3);
	printf("Attempting to add %d\n",1);
	stack_enqueue(test1,1);	
	printf("Attempting to add %d\n",2);
	stack_enqueue(test1,2);	
	printf("Attempting to add %d\n",3);
	stack_enqueue(test1,3);	
	printf("Attempting to add %d\n",4);
	stack_enqueue(test1,4);	
	printf("Removing: %d\n",stack_dequeue(test1));	
	printf("Removing: %d\n",stack_dequeue(test1));	
	printf("Removing: %d\n",stack_dequeue(test1));	

	printf("Attempting to add %d\n",5);
	stack_enqueue(test1,5);	
	printf("Attempting to add %d\n",6);
	stack_enqueue(test1,6);	
	printf("Attempting to add %d\n",7);
	stack_enqueue(test1,7);	
	printf("Removing: %d\n",stack_dequeue(test1));	

	free_stack(test1);
}

void unitTest2(){
	stack_t* test2 = create_stack(10);
	//stack_enqueue(test2,9);	
	printf("size of the stack: %d\n", test2->capacity);
	printf("Removing: %d\n",stack_dequeue(test2));	
	free_stack(test2);
	
}
// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

	// List of Unit Tests to test your data structure	
	unitTest1();
	unitTest2();
	return 0;
}

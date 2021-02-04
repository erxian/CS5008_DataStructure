// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "myqueue.h"
// Note that we are locating this file
// within the same directory, so we use quotations 
// and provide the path to this file which is within
// our current directory.


// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.
void unitTest1(){

	queue_t* test1 = create_queue(3);
	printf("Attempting to add %d\n", 1);
	queue_enqueue(test1, 1);
	printf("Attempting to add %d\n", 2);
	queue_enqueue(test1, 2);
	printf("Attempting to add %d\n", 3);
	queue_enqueue(test1, 3);

	printf("the data is: %d\n", *(test1->data));
	printf("the data is: %d\n", *(test1->data + 1));
	printf("the data is: %d\n", *(test1->data + 2));

	printf("Removing: %d\n", queue_dequeue(test1));	
	printf("Removing: %d\n", queue_dequeue(test1));	
	

	printf("Attempting to add %d\n", 4);
	queue_enqueue(test1, 4);
	printf("Attempting to add %d\n", 5);
	queue_enqueue(test1, 5);
	
	printf("the data is: %d\n", *(test1->data));
	printf("the data is: %d\n", *(test1->data + 1));
	printf("the data is: %d\n", *(test1->data + 2));

	printf("Removing: %d\n", queue_dequeue(test1));
	printf("Removing: %d\n", queue_dequeue(test1));

	printf("the data is: %d\n", *(test1->data));
	printf("the data is: %d\n", *(test1->data + 1));
	printf("the data is: %d\n", *(test1->data + 2));
	
	free_queue(test1);
}


void unitTest2(){
	queue_t* test2 = create_queue(3);
	printf("Attempting to add %d\n", 1);
	queue_enqueue(test2, 1);
	printf("Attempting to add %d\n", 2);
	queue_enqueue(test2, 2);
	printf("Attempting to add %d\n", 3);
	queue_enqueue(test2, 3);

	printf("the data is: %d\n", *(test2->data));
	printf("the data is: %d\n", *(test2->data + 1));
	printf("the data is: %d\n", *(test2->data + 2));
	
	queue_enqueue(test2, 4);
		
	printf("the data is: %d\n", *(test2->data));
	printf("the data is: %d\n", *(test2->data + 1));
	printf("the data is: %d\n", *(test2->data + 2));
}


void unitTest3(){
	queue_t* test3 = create_queue(3);
	printf("Removing: %d\n", queue_dequeue(test3));

}

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

	// List of Unit Tests to test your data structure
	printf("===========unitTest1============\n");
	unitTest1();
	printf("================================\n");
	// enqueue a full queue
	printf("===========unitTest2============\n");
	unitTest2();
	printf("================================\n");
	// dequeue an empty queue
	printf("===========unitTest3============\n");
	unitTest3();
	printf("================================\n");

	return 0;
}

// Compile this assignment with: gcc -g -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.



// ====================================================
// ================== Program Entry ===================
// ====================================================

int unitTest3(){
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_back(test,142);
    if(1==dll_size(test)){
       passed = 1;
    }else{
       passed = 0;
    }
    free_dll(test);

    return passed;
}

// Tests push_front and size functions
int unitTest2(){
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_front(test,789);
    printf("get size %d\n", dll_size(test));
    dll_push_front(test,555);
    printf("get size %d\n", dll_size(test));
    dll_push_front(test,666);
    printf("get size %d\n", dll_size(test));
    dll_push_front(test, 111);
    printf("get size %d\n", dll_size(test));
    dll_push_back(test, 222);
    printf("get size %d\n", dll_size(test));
    dll_insert(test, 0, 444);
    printf("get size %d\n", dll_size(test));
    dll_insert(test, 0, 777);
    printf("get size %d\n", dll_size(test));
    //printf("get number %d\n", dll_get(test, 3));
    //printf("pop back %d\n", dll_pop_back(test));
    //printf("pop front %d\n", dll_pop_front(test));
    dll_remove(test, 3);
    printf("get size %d\n", dll_size(test));
    if(4==dll_size(test)){
       passed = 1;
    }else{
        passed = 0;
    }
    printDll(test);

    free_dll(test);

    return passed;
}

int main(){
   // dll_t * dll = create_dll();
//	int result = unitTest1();
	int result = unitTest3();
	printf("%d\n", result);
    
    
    
    return 0;
}

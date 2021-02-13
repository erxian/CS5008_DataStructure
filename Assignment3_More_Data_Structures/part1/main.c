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
int unitTest4(){
    int passed = 0;
    dll_t* test = create_dll();
    dll_push_back(test,142);
//    printDll(test);
    dll_pop_back(test);
 //   printDll(test);
    if(0==dll_size(test)){
       passed = 1;
    }else{
        passed = 0;
    }
    free_dll(test);

    return passed;
}


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
    dll_push_back(test,666);
    printf("get size %d\n", dll_size(test));
    dll_push_front(test, 111);
    printf("get size %d\n", dll_size(test));
    dll_push_back(test, 222);
    printf("get size %d\n", dll_size(test));
    printf("-------------\n");
    dll_remove(test, 0);
    printf("get size %d\n", dll_size(test));
    dll_remove(test, 3);
    printf("get size %d\n", dll_size(test));
    if(3==dll_size(test)){
       passed = 1;
    }else{
        passed = 0;
    }
   // printDll(test);

    free_dll(test);

    return passed;
}

int main(){
   // dll_t * dll = create_dll();
//	int result = unitTest1();
	int result4 = unitTest4();
	int result3 = unitTest3();
	int result2 = unitTest2();
	printf("%d\n", result4);
	printf("%d\n", result3);
	printf("%d\n", result2);
    
    
    
    return 0;
}

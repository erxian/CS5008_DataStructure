#include <stdio.h>
#include "my_hashmap.h"

int unitTest(){
    // Create our hashmap
    hashmap_t* myHashmap = hashmap_create(5); 
    // Insert a first key/value pair
    hashmap_insert(myHashmap,"pig", "a farm animal");
    //printf("pig was added should be 1: %d\n",hashmap_hasKey(myHashmap,"pig"));
    //hashmap_insert(myHashmap,"cat", "a fat pet");
    //hashmap_insert(myHashmap,"mmm", "a mmmm pet");
    //hashmap_insert(myHashmap,"qqq", "a qqq pet");
    //hashmap_printKeys(myHashmap);
    //printf("cat's value is %s\n",hashmap_getValue(myHashmap, "cat"));
    //hashmap_removeKey(myHashmap,"pig");
    //printf("mmm was added should be 0: %d\n",hashmap_hasKey(myHashmap,"mmm"));
    //printf("cat was added should be 1: %d\n",hashmap_hasKey(myHashmap,"cat"));
    hashmap_update(myHashmap,"pig","a really cool farm animal");    
    hashmap_printKeys(myHashmap);
    hashmap_delete(myHashmap);
}

int unitTest1(){
    // Create our hashmap
    hashmap_t* myHashmap = hashmap_create(5); 
    // Insert a first key/value pair
    hashmap_insert(myHashmap,"pig", "a farm animal");
    // Does hashmap contain key?
    printf("pig was added should be 1: %d\n",hashmap_hasKey(myHashmap,"pig"));
    // Print out the keys
    hashmap_printKeys(myHashmap);
    // Retrieve pig's value 
    printf("pig's value is %s\n",hashmap_getValue(myHashmap, "pig"));
    hashmap_update(myHashmap,"pig","a really cool farm animal");    
    printf("pig's value is updated to: %s\n",hashmap_getValue(myHashmap, "pig"));
    // Remove a key
    hashmap_removeKey(myHashmap,"pig");
    // Does hashmap contain key?
    printf("pig was removed should be 0: %d\n",hashmap_hasKey(myHashmap,"pig"));
    // Finally terminate our hashmap
    hashmap_delete(myHashmap);
}

int unitTest2(){
    // Create our hashmap
    hashmap_t* myHashmap = hashmap_create(5); 
    // Insert a first key/value pair
    hashmap_insert(myHashmap,"pig", "a farm animal");
    hashmap_insert(myHashmap,"bat", "a farm creature");
    hashmap_insert(myHashmap,"cat", "a funny farm animal");
    hashmap_insert(myHashmap,"dog", "a fun farm animal");
    hashmap_insert(myHashmap,"bear", "a wild farm animal");
    hashmap_insert(myHashmap,"ox", "another farm animal");
    hashmap_insert(myHashmap,"cow", "a favorite farm animal");
    hashmap_insert(myHashmap,"hippo", "a farm animal?");
    hashmap_insert(myHashmap,"elephant", "not a farm animal");
    hashmap_insert(myHashmap,"human", "an animal that farms");
    // Print the keys
    hashmap_printKeys(myHashmap);
    // Finally terminate our hashmap
    hashmap_delete(myHashmap);

}
int main(){
    unitTest();
    //printf("============ unitTest1() ================\n");
    //unitTest1();
    //printf("============ unitTest2() ================\n");
    //unitTest2();
    
    return 0;
}

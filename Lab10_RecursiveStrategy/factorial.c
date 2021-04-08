// gcc factorial.c -o factorial
// ./factorial

#include <stdio.h>

// TODO: Implement iterative solution here
unsigned long long int factorial(int n){
	// if n equals to 0 or 1, return
	if (n == 0 || n == 1) {
		return 1;
	} 

	unsigned long long int fact = 1;
	int i;

	for (i = 1; i <= n; i++) {	
		fact = fact * i;	
	}
	
  	return fact;
}

// TODO: Implement recursive solution here
unsigned long long int factorial_rec(int n){
	// Base Case
  	if (n == 0 || n == 1) {
		return 1;
  	} 
	// Recursive Call	
	return n * factorial_rec(n-1);
}

int main(){

  // Both of these should print the same result!
  printf("factorial(20) = %llu\n",factorial(20));
  printf("factorial_rec(20) = %llu\n",factorial_rec(20));

  return 0;
}

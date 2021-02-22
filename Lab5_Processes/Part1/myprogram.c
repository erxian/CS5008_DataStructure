// Type in and try example5.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

	char* myargv1[16];	// We can store up to 16 arguments.
	myargv1[0] = "/bin/ls";	// Our first argument is the program we want to launch.
	myargv1[1] = "/home/evelyn/CS5008/monorepo-erxian/Lab5_Processes/Part1/"; 	//Any additional arguments (i.e. flags) we want to make use of.

	myargv1[2] = NULL; 	// Terminate the argument list--similar to how we would terminate a character string.
				// (i.e. Set the last argument to NULL if we have no more flags.)
	
	char* myargv2[16];	// We can store up to 16 arguments.
	myargv2[0] = "/bin/echo";	// Our first argument is the program we want to launch.
	myargv2[1] = "testing"; 	// Terminate the argument list--similar to how we would terminate a character string.
	myargv2[2] = NULL;

	char* myargv3[16];	// We can store up to 16 arguments.
	myargv3[0] = "/bin/nl";	// Our first argument is the program we want to launch.
	myargv3[1] = "example1.c"; 	// Terminate the argument list--similar to how we would terminate a character string.
	myargv3[2] = NULL;
	

	pid_t p1 = fork();	
	if (p1 == 0) {
		// Executes command from child then terminates our process
		// Note: There are other 'exec' functions that may be helpful.
		execve(myargv1[0], myargv1, NULL);
		printf("Child1: Should never get here\n");
		return 0;
	}
	
	pid_t p2 = fork();
	if (p2 == 0) {
		sleep(1);
		execve(myargv2[0], myargv2, NULL);
		printf("Child2: Should never get here\n");
		return 0;
	}

	pid_t p3 = fork();
	if (p3 == 0) {
		sleep(2);
		execve(myargv3[0], myargv3, NULL);
		printf("Child3: Should never get here\n");
		return 0;
	}

	int st1, st2, st3;
	waitpid(p1, &st1, 0); // handy synchronization function again!
	waitpid(p2, &st2, 0); // handy synchronization function again!
	waitpid(p3, &st3, 0); // handy synchronization function again!
	//printf("in parent, child 1 pid = %d\n", p1); 
	//printf("in parent, child 2 pid = %d\n", p2); 
	//printf("in parent, child 3 pid = %d\n", p3); 
	printf("This always prints last\n");
	
	return 0;
}

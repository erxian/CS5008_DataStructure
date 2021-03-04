// Implement your part 1 solution here
// gcc vfork.c -o vfork
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Modify your paint function here
void paint(int workID) { 
	printf("Artist %d is painting\n",workID);
}

int main(int argc, char** argv){

        int numberOfArtists = 8; // How many child processes do we want?

	pid_t pid;
	// main loop where we fork new threads
	int i;
        for (i=0; i < numberOfArtists; i++) {
                // (1) Perform a fork
                pid = fork();
		
		
                // (2) Make only the child do some work (i.e. paint) and then terminate.
                if (pid == 0) {
			// TODO: make child paint
			// TODO: Then terminate/exit child
			paint(i);
			exit(0);
		}
		printf("child pid: %d\n", pid);
        }

        printf("parent is exiting(last artist out!)\n");

        return 0;
}

// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 64

char colors[64][64*3];


void save() {
// Write out the PPM file
        // If you are looking at this solution, it could
        // be better laid out in a 'save function'
        FILE *fp;
        fp = fopen("threads.ppm","w+");
        fputs("P3\n",fp);
        fputs("64 64\n",fp);
        fputs("255\n",fp);
        int i, j;
        for(i =0; i < 64;i++){
                for(j =0; j < 64*3; j++){
                        fprintf(fp,"%d",colors[i][j]);
                        if ((j+1)%3 == 0) {
                                fputs("  ",fp);
                        } else {
                                fputs(" ",fp);
                        }
                }
                fputs("\n",fp);
        }
        fclose(fp);
}


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int workID = 0;

// Modify your paint function here
void *paint(void *arg) {
	pthread_mutex_lock(&mutex1);
        printf("Artist %d is painting\n",workID);
        int i;
        for (i=0; i < 64*3; i++) {	
                colors[workID][i] = workID + i % 64;
        }
	workID += 1;
	pthread_mutex_unlock(&mutex1);
	return NULL;
}


int main() {
	pthread_t tids[NTHREADS];
	int i;
	for (i=0; i < NTHREADS; ++i) {
		pthread_create(&tids[i], NULL, paint, NULL);
	}

	for (i=0; i < NTHREADS; ++i) {
		pthread_join(tids[i], NULL);
	}
	save();	
	return 0; 

}

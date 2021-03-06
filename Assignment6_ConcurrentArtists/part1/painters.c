// Compile by either typing 'make' in the terminal 
// or manually with 'clang -lpthread painters.c -o painters'

// ===================== Include Libraries =====================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
// ===================== Setup our Canvas =====================
#define CANVAS_WIDTH 256
#define CANVAS_HEIGHT 256

// Our canvas is a shared piece of memory that each artist can access.
// Within our canvas, every pixel has a red, green, and blue component.
// Because we only want one artist at a time drawing on a pixel
// each pixel also has a lock associated with it.
typedef struct pixel{
	int r,g,b;
	pthread_mutex_t lock;
}pixel_t;

// Create our canvas as a global variable.
// This canvas will be shared amongst all of our threads.
pixel_t canvas[CANVAS_WIDTH][CANVAS_HEIGHT];

// ===================== Setup our Artists =====================
// This is our data structure for each artist
typedef struct artist{
	int x,y;	// Store the position of where an artist is painting
	int r,g,b;	// The color an artist paints in.
	//int count;
}artist_t;

// An artist can move in one of the following directions
// This is a handy abstraction, as I can 'roll an 8-sided dice'
// and depending on what value that is, move in an x and y position
// corresponding with the index below.
// e.g.
// A roll of 0 moves my artist (-1,0).
// A roll of 7 moves my artist (-1,-1)
const int moves = 8;
const int movement[][2] ={
    {-1, 0}, // to the left 
    {-1, 1}, // to the left and down
    {0, 1}, // down
    {1, 1}, // to the right and down
    {1, 0}, // to the right
    {1, -1}, // to the right and up
    {0, -1}, // up
    {-1, -1} // to the left and up
};


// This function sets up the canvas
// The purpose is to iterate through every pixel and 
// setup the initial values of the pixel and initialize the
// lock structure.
// The intent is to call this function early in main.
void initCanvas(){
	for(int x =0; x < CANVAS_WIDTH; ++x){
		for(int y =0; y < CANVAS_HEIGHT; ++y){
			canvas[x][y].r = 255;
			canvas[x][y].g = 255;
			canvas[x][y].b = 255;
			pthread_mutex_init(&canvas[x][y].lock, NULL);
		}
	}
}

// This function saves the canvas as a PPM.
// This function should be called after all painting
// operations have completed.
void outputCanvas(){
// Write out the PPM file
	// If you are looking at this solution, it could
	// be better laid out in a 'save function'
	FILE *fp;
	fp = fopen("canvas.ppm","w+");
	fputs("P3\n",fp);
	fputs("256 256\n",fp);
	fputs("255\n",fp);
	for(int x =0; x < CANVAS_WIDTH; ++x){
		for(int y =0; y < CANVAS_HEIGHT; ++y){
			fprintf(fp,"%d",canvas[x][y].r);
			fputs(" ",fp);		
			fprintf(fp,"%d",canvas[x][y].g);
			fputs(" ",fp);		
			fprintf(fp,"%d",canvas[x][y].b);
			fputs(" ",fp);		
		}
		fputs("\n",fp);
	}
	fclose(fp);	
}

// paint on canvas
void* paint(void* args){
    // Convert our argument structure to an artist
    	artist_t* painter = (artist_t*)args;

    // Our artist will now attempt to paint 5000 strokes of paint
	// on our shared canvas
	for(int i=0; i < 5000; ++i){

        // Generate a random number from 0-7
        int roll = (rand()%8);
	// get nextX and nextY
        int nextX = painter->x + movement[roll][0];
        int nextY = painter->y + movement[roll][1];
        // Clamp the range of our movements so we only
        // paint within our 256x256 canvas.
        if(nextX < 0) {  nextX= 0; }
        if(nextX >  CANVAS_WIDTH-1) { nextX  = CANVAS_WIDTH-1; }
        if(nextY< 0) { nextY = 0; }
        if(nextY > CANVAS_HEIGHT-1) { nextY = CANVAS_HEIGHT-1; }
  
	pixel_t* pixel = &canvas[nextX][nextY];
 
	pthread_mutex_lock( &(pixel->lock) );
	if( canvas[nextX][nextY].r == 255 &&
	    canvas[nextX][nextY].g == 255 &&
	    canvas[nextX][nextY].b == 255){
	        canvas[nextX][nextY].r = painter->r;
	        canvas[nextX][nextY].g = painter->g;
	        canvas[nextX][nextY].b = painter->b;	
		// change current x to nextX, current y to nextY	
	    	painter->x = nextX;
	    	painter->y = nextY;
		//painter->count += 1;
	// if the color is not painter's color, backtrack	
	} else if (canvas[nextX][nextY].r == painter->r &&
		canvas[nextX][nextY].g == painter->g &&
		canvas[nextX][nextY].b == painter->b) {
		// If we cannot paint the pixel, then we backtrack
		// to a previous pixel that we own.
	    	painter->x = nextX;
	    	painter->y = nextY;
	} else {
		; // the position in nextX, nextY has the same color with this painter

	}	
	pthread_mutex_unlock( &(pixel->lock) );
    }
}

// create artist Michaelangelo
artist_t* create_Michaelangelo() {
	artist_t* Michaelangelo = malloc(sizeof(artist_t));

	// Fill in the artist attributes
	Michaelangelo->x = 0;
	Michaelangelo->y = 0;
	Michaelangelo->r = 255;
	Michaelangelo->g = 0;
	Michaelangelo->b = 165;
	//Michaelangelo->count = 1;
	//canvas[Michaelangelo->x][Michaelangelo->y].r = Michaelangelo->r; 	
	//canvas[Michaelangelo->x][Michaelangelo->y].g = Michaelangelo->g; 	
	//canvas[Michaelangelo->x][Michaelangelo->y].b = Michaelangelo->b; 	

	return Michaelangelo;
}

// create artist Donatello
artist_t* create_Donatello() {
	artist_t* Donatello  = malloc(sizeof(artist_t));

	// Fill in the artist attributes
	Donatello->x = CANVAS_WIDTH-1;
	Donatello->y = 0;
	Donatello->r = 128;
	Donatello->g = 0;
	Donatello->b = 128;
	//Donatello->count = 1;	
	//canvas[Donatello->x][Donatello->r].r = Donatello->r;
	//canvas[Donatello->x][Donatello->r].g = Donatello->g;
	//canvas[Donatello->x][Donatello->r].b = Donatello->b;

	return Donatello;
}


// create artist Raphael
artist_t* create_Raphael() {
	
	artist_t* Raphael = malloc(sizeof(artist_t));
	// Fill in the artist attributes
	Raphael->x = CANVAS_WIDTH-1;
	Raphael->y = CANVAS_HEIGHT-1;
	Raphael->r = 255;
	Raphael->g = 0;
	Raphael->b = 0;	
	//Raphael->count = 1;	
	//canvas[Raphael->x][Raphael->y].r = Raphael->r;
	//canvas[Raphael->x][Raphael->y].g = Raphael->g;
	//canvas[Raphael->x][Raphael->y].b = Raphael->b;
	
	return Raphael;
}

//create artist Leonardo
artist_t* create_Leonardo() {
	artist_t* Leonardo = malloc(sizeof(artist_t));
	// Fill in the artist attributes
	Leonardo->x = 0;
	Leonardo->y = CANVAS_HEIGHT-1;
	Leonardo->r = 0;
	Leonardo->g = 0;
	Leonardo->b = 255;
	//Leonardo->count = 1;	
	//canvas[Leonardo->x][Leonardo->y].r = Leonardo->r;
	//canvas[Leonardo->x][Leonardo->y].g = Leonardo->g;
	//canvas[Leonardo->x][Leonardo->y].b = Leonardo->b;
	
	return Leonardo;
}


// Add 50 more artists
artist_t** create_moreArtists(int rookieArtists) {
	artist_t** moreArtists = (artist_t**)malloc(sizeof(artist_t*) * rookieArtists);
	int createdArtists = 0;
	for(int i=0; i < rookieArtists; ++i){
		int colorPresent = 1;  // true
		while (colorPresent) {
			int r = rand() % 256;	
			int g = rand() % 256;	
			int b = rand() % 256;	
		
			int colorUsed = 0; //false	

			for (int j=0; j < createdArtists; j++) {
				if (moreArtists[j]->r == r && moreArtists[j]->g == g &&
					moreArtists[j]->b == b) {
					printf("color used\n");
					colorUsed = 1;
					break;
				}
			}
			if (!colorUsed) {
        			moreArtists[i] = malloc(sizeof(artist_t));	
				// initialize starting position randomly;
				moreArtists[i]->x = (rand()%255);
				moreArtists[i]->y = (rand()%255);
				// initialize paint color randomly;
				moreArtists[i]->r = r;
				moreArtists[i]->g = g; 
				moreArtists[i]->b = b;
				//moreArtists[i]->count = 1;
				//canvas[moreArtists[i]->x][moreArtists[i]->y].r = r;
				//canvas[moreArtists[i]->x][moreArtists[i]->y].g = g;
				//canvas[moreArtists[i]->x][moreArtists[i]->y].b = b;
				
				createdArtists++;
				colorPresent = 0;
			}
		}
	}
	return moreArtists;
}


// ================== Program Entry Point ============
int main(){
	// Initialize our 'blank' canvas
	initCanvas();
	
	// Our four expert artists
	artist_t* Michaelangelo = create_Michaelangelo(); 	
	artist_t* Donatello = create_Donatello(); 
	artist_t* Raphael = create_Raphael();
	artist_t* Leonardo = create_Leonardo();
	// create 50 more artists
        int rookieArtists = 50;
	artist_t** moreArtists = create_moreArtists(rookieArtists);

    // Hold our thread id's
	pthread_t Michaelangelo_tid;
	pthread_t Donatello_tid;
	pthread_t Raphael_tid;
	pthread_t Leonardo_tid;
        pthread_t moreArtists_tid[rookieArtists];
    // Initialize a seed for our random number generator
    	srand(time(NULL));
	
	// Create our threads for each of our expert artists
	pthread_create(&Michaelangelo_tid,NULL,(void*)paint,Michaelangelo);
	pthread_create(&Donatello_tid,NULL,(void*)paint,Donatello);
	pthread_create(&Raphael_tid,NULL,(void*)paint,Raphael);
	pthread_create(&Leonardo_tid,NULL,(void*)paint,Leonardo);
	
        for(int i =0; i < rookieArtists; ++i){
		pthread_create(&moreArtists_tid[i], NULL, (void*)paint, moreArtists[i]);
	}

	// Join each with the main thread.  
	// Do you think our ordering of launching each thread matters?
	pthread_join(Michaelangelo_tid, NULL);		   
	pthread_join(Donatello_tid, NULL);		   
	pthread_join(Raphael_tid, NULL);		   
	pthread_join(Leonardo_tid, NULL);		   

    // TODO: Add the join the 50 other artists threads here	
        for(int i =0; i < rookieArtists; ++i){
    		pthread_join(moreArtists_tid[i], NULL);
    	}


	for(int i =0; i < rookieArtists; ++i){
		printf("x=%d, y=%d, rgb=%d %d %d\n", 
			moreArtists[i]->x, moreArtists[i]->y,
			moreArtists[i]->r, moreArtists[i]->g, moreArtists[i]->b);
	}
    // Save our canvas at the end of the painting session
	outputCanvas();
	// Terminate our program
	free(Michaelangelo);
    	free(Donatello);
    	free(Raphael);
    	free(Leonardo);
    
    // TODO: Free any other memory you can think of
    	for(int i =0; i < rookieArtists; ++i){
		free(moreArtists[i]);
    	}
	free(moreArtists);
	return 0;
}

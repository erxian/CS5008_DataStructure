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
	//int count;    // count how many times the painter paint, observe starvation
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
	int x;
	for(x=0; x < CANVAS_WIDTH; ++x){
		int y;
		for(y=0; y < CANVAS_HEIGHT; ++y){
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
	int x;	
	for(x=0; x < CANVAS_WIDTH; ++x){
		int y;	
		for(y=0; y < CANVAS_HEIGHT; ++y){
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

// This function will paint on canvas, it takes painter as the
// argument. First, the painter will randomly generate a next position
// it aims to paint. Second lock the next pixel in case other painters
// change the color. Third, check the next pixel color, if the color is white,
// then paint it, if the color is the same as painter's color, then move to
// the next pixel, if the color is other color, stay in current postion and
// do nothing. 
void* paint(void* args){
    // Convert our argument structure to an artist
    	artist_t* painter = (artist_t*)args;
    // Our artist will now attempt to paint 5000 strokes of paint
	// on our shared canvas
	int i;
	for(i=0; i < 5000; ++i){
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
	// if the color is white, paint it
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
	} else if (canvas[nextX][nextY].r == painter->r &&
		canvas[nextX][nextY].g == painter->g &&
		canvas[nextX][nextY].b == painter->b) {
		// if the color is the same as painter's color, move to this pixel	
	    	painter->x = nextX;
	    	painter->y = nextY;
	} else { 
	 	// else if the color is other painter's color, do nothing
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
	  // paint the starting positon
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
	  // paint the starting positon
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
	  // paint the starting positon
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
	  // paint the starting positon
	//canvas[Leonardo->x][Leonardo->y].r = Leonardo->r;
	//canvas[Leonardo->x][Leonardo->y].g = Leonardo->g;
	//canvas[Leonardo->x][Leonardo->y].b = Leonardo->b;
	
	return Leonardo;
}

// This function will create one artist, assign randomly start
// postion to him, and assign given color to him.
artist_t* create_Artist(int r, int g, int b) {
	artist_t* artist = (artist_t*)malloc(sizeof(artist_t));
	// initialize starting position randomly;
	artist->x = (rand()%255);
	artist->y = (rand()%255);
	artist->r = r;
	artist->g = g;
	artist->b = b;
	// artist->count = 1;
	  // paint the starting positon
	//canvas[x][y].r = r;
	//canvas[x][y].g = g;
	//canvas[x][y].b = b;
	
	return artist;
}

// Add 50 more artists, every artist will randomly generate
// a starting postion and color, artists will not have the same
// color.
artist_t** create_moreArtists(int rookieArtists) {
	artist_t** moreArtists = (artist_t**)malloc(sizeof(artist_t*)*rookieArtists);
	int createdArtists = 0;
	int i;
	for(i=0; i < rookieArtists; ++i){
		int colorPresent = 1;  // true
		while (colorPresent) {
			int r = rand() % 256;	
			int g = rand() % 256;	
			int b = rand() % 256;	
		
			int colorUsed = 0; //false	
			int j;
			for (j=0; j < createdArtists; j++) {
				if (moreArtists[j]->r == r && moreArtists[j]->g == g &&
				    moreArtists[j]->b == b) {
					printf("color used\n");
					colorUsed = 1;
					break;
				}
			}
			if (!colorUsed) {
				// create artist
				moreArtists[i] = create_Artist(r, g, b);
				createdArtists++;
				colorPresent = 0;  //false
			}
		}
	}
	return moreArtists;
}

// destroy all mutex we have created
void destroy_Mutex() {
	int x;
	for(x=0; x < CANVAS_WIDTH; ++x){
		int y;
		for(y=0; y < CANVAS_HEIGHT; ++y){
			pthread_mutex_destroy(&canvas[x][y].lock);
		}
	}
}

// ================== Program Entry Point ============
int main(){
	initCanvas();  // Initialize our 'blank' canvas
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
	pthread_create(&Michaelangelo_tid, NULL, (void*)paint, Michaelangelo);
	pthread_create(&Donatello_tid, NULL, (void*)paint, Donatello);
	pthread_create(&Raphael_tid, NULL, (void*)paint, Raphael);
	pthread_create(&Leonardo_tid, NULL, (void*)paint, Leonardo);
	// create threads for 50 rookie artists
	int i;	
        for(i=0; i < rookieArtists; ++i){
		pthread_create(&moreArtists_tid[i], NULL, (void*)paint, moreArtists[i]);
	}
	// Join each with the main thread.  
	pthread_join(Michaelangelo_tid, NULL);		   
	pthread_join(Donatello_tid, NULL);		   
	pthread_join(Raphael_tid, NULL);		   
	pthread_join(Leonardo_tid, NULL);		   
    	// join the 50 rookie artists threads here	
        for(i=0; i < rookieArtists; ++i){
    		pthread_join(moreArtists_tid[i], NULL);
    	}
    	// Save our canvas at the end of the painting session
	outputCanvas();
	// Terminate our program
	free(Michaelangelo); // free Michaelangelo
    	free(Donatello);  // free Donatello
    	free(Raphael);  // free Raphael
    	free(Leonardo);  // free Leonardo
    	for(i=0; i < rookieArtists; ++i){
		free(moreArtists[i]);  // free 50 rookie artists
    	}
	free(moreArtists);  // free array stores to rookie artists
	destroy_Mutex();   // destroy the mutex we have created
	return 0;
}

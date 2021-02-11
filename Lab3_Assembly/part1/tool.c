// Implement your cycle count tool here.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){

	//char instruList[9] = {"ADD", "SUB", "MUL", "DIV", "MOVE", "LEA", "PUSH", "POP", "RET"}; 
	char *instruList[9] = {"add", "sub", "mul", "div", "mov", "lea", "pus", "pop", "ret"}; 
	
	//printf("argc is the argument count: %d\n", argc);
	
	//for(int i=0; i < argc; i++){
	//	printf("argv[%d] is %s\n", i, argv[i])
	//}
	
	FILE* file = fopen(argv[1], "r");
	size_t len = 255;
	char *line = malloc(sizeof(char) * len);
	// check if the file exists
	if (file == NULL){
		exit(1);
	}
	
	int total_instru = 0;
	int total_cycles = 0;
	// read file line by line
	while(fgets(line, len, file) != NULL){;
		int i = 0;
		// find the first non space char index
		while(line[i] == ' '){
	 		i++;
	 	}

	 	char firstThreeChar[3];
		// get the first 3 characters
	 	strncpy(firstThreeChar, line+i+1, 3);
		// iterate to check if this line is a valid instrucion
		for (int i = 0; i < 9; i++){
	 		if (strcmp(firstThreeChar, instruList[i]) == 0){
				// MUL has 2 cycles
				if (strcmp(firstThreeChar, "mul") == 0){
					total_cycles += 2;
				// DIV has 4 cycles
				} else if (strcmp(firstThreeChar, "div") == 0){
					total_cycles += 4;
				// other instrctions have 1 cycle
				} else {
					total_cycles += 1;
				}
				total_instru += 1;
			}
		}

	}
	printf("total instructions: %d\n", total_instru);
	printf("total cycles: %d\n", total_cycles);
	
	free(line);
	
	return 0;
}

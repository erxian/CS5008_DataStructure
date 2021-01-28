#include <stdio.h>
#include <stdlib.h>

int main() {
	int round = 5;
	int inputInteger;
	int guessAbility[5];
	for (int i = 0; i < round; i++) {
		int randomInteger;
		int guessTime = 1;
		randomInteger = rand() % 10 + 1;
		printf("==========================\n");
		printf("CPU Says: Pick a number 1-10\n");
		printf("==========================\n");
		printf("Make a guess: ");
		scanf("%d", &inputInteger);
		while (inputInteger != randomInteger) {
			if (inputInteger < randomInteger) {
				printf("No guess higher!\n");
			} else {
				printf("No guess lower!\n");
			}
			guessTime++;
			printf("Make a guess: ");
			scanf("%d", &inputInteger);
		}
		printf("You got it!\n");
		guessAbility[i] = guessTime;
	}
	printf("=================================================\n");
	printf("|Here are the results of your guessing abilities|\n");
	printf("=================================================\n");
	for (int i = 0; i < round; i++) {
		printf("Game %d took you %d guesses\n", i, guessAbility[i]);
	}
	return 0;
}

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	srand(time(0));
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			remodel, smithy, village, baron, great_hall};
	struct gameState* G; //= newGame();
	struct gameState* gCopy; //= newGame();
	
	printf("Random testing sea hag Card:\n");

	int i, maxTests, testNumPlayer, testHandSize, testDeckSize;
	maxTests = 10;

	for(i = 0; i < maxTests; i++){
		G = newGame();
		gCopy = newGame();
		
		testNumPlayer = rand() % 4 + 1;
		initializeGame(testNumPlayer, k, seed, G);
		//int chosenPlayer = rand() % 4;
		testHandSize = rand() % 10 + 1;
		testDeckSize = rand() % 91 + 10;
		
		int j, k;
		for(j = 0; j < testNumPlayer; j++){
			for(k = 0; k < testDeckSize; k++){
				G->deck[j][k] = rand() % 25;
			}
			G->deckCount[j] = testDeckSize;
		}

		for(j = 0; j < testNumPlayer; j++){
			for(k = 0; k < testDeckSize; k++){
				G->hand[j][k] = rand() % 25;
			}
			G->handCount[j] = testHandSize;
		}
		
		for(k = 0; k < testNumPlayer; k++){
			shuffle(k, G);
			G->discardCount[k] = 0;
		}

		memcpy(gCopy, G, sizeof(struct gameState));

		
		int randPlayer = rand() % testNumPlayer; 
		//for(k = 0; k < testNumPlayer; k++){
		seaHagCardEffect(G, randPlayer);
		//}
		
		for(k = 0; k < testNumPlayer; k++){
			if (k != randPlayer){
				if(gCopy->deckCount[k] != G->deckCount[k]){
					printf("One card should have been removed from the deck and then a curse added, original count: %d, after count: %d\n", gCopy->deckCount[k], G->deckCount[k]);
					fflush(stdout);
				}
				if(gCopy->deck[k][gCopy->deckCount[k] - 1] != G->discard[k][G->discardCount[k] - 1]){
					printf("Incorrect card added to discard pile\n");
					fflush(stdout);
				}
				if(G->deck[k][G->deckCount[k] - 1] != curse){
					printf("curse card not on the top of the deck\n");
					fflush(stdout);
				}
			}

		}
	}

	printf("Finished running %d tests\n", maxTests);
	fflush(stdout);

	return 0;
}


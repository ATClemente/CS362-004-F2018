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
	//int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			remodel, smithy, village, baron, great_hall};
	struct gameState* G; //= newGame();
	struct gameState* gCopy; //= newGame();
	//initializeGame(numPlayer, k, seed, G);
	
	printf("Random testing smithy Card:\n");

	int i, maxTests, testNumPlayer, testHandSize, testDeckSize;
	maxTests = 1000000;
	
	for(i = 0; i < maxTests; i++){
		G = newGame();
		gCopy = newGame();
		
		testNumPlayer = rand() % 4 + 1;
		initializeGame(testNumPlayer, k, seed, G);
		int chosenPlayer = rand() % 4;
		testHandSize = rand() % 10 + 1;
		testDeckSize = rand() % 91 + 10;	

		int j;
		for(j = 0; j < testDeckSize; j++){
			G->deck[chosenPlayer][j] = rand() % 25;
		}
		//G->deck[chosenPlayer][0] = rand() % 3 + 4;	
		//G->deck[chosenPlayer][1] = rand() % 3 + 4;
		G->deckCount[chosenPlayer] = testDeckSize;	

		for(j = 0; j < testHandSize; j++){
			G->hand[chosenPlayer][j] = rand() % 25;
		}
		G->handCount[chosenPlayer] = testHandSize;

		shuffle(chosenPlayer, G);
		G->discardCount[chosenPlayer] = 0;
		int smithySpot = rand() % testHandSize;
		G->hand[chosenPlayer][smithySpot] = smithy;
		memcpy(gCopy, G, sizeof(struct gameState));
		smithyCardEffect(G, chosenPlayer, smithySpot);

		if(gCopy->handCount[chosenPlayer] != G->handCount[chosenPlayer] - 2){
			printf("Did not add three cards to hand, iteration %d\nPre: %d, Post: %d\n", i, gCopy->handCount[chosenPlayer], G->handCount[chosenPlayer]);
			fflush(stdout);
		}
		
		if(G->playedCards[G->playedCardCount - 1] != smithy){
			printf("Top of played pile was not a smithy card\n");
			fflush(stdout);
		}

		int errorCount = 0;
		int preDeckCard, postHandCard;
		int cardsDrawn = G->handCount[chosenPlayer] - gCopy->handCount[chosenPlayer] + 1;
		for(j = 0; j < cardsDrawn - 1; j++){
			
			preDeckCard = gCopy->deck[chosenPlayer][gCopy->deckCount[chosenPlayer] - 1 - j];
			
			postHandCard = G->hand[chosenPlayer][G->handCount[chosenPlayer] - cardsDrawn + 1 + j];
			
			if(postHandCard != preDeckCard){
				errorCount++;
			}
		}

		

		preDeckCard = gCopy->deck[chosenPlayer][gCopy->deckCount[chosenPlayer] - cardsDrawn];

		if(preDeckCard != G->hand[chosenPlayer][smithySpot]){
			errorCount++;
		}

		if(errorCount != 0){
			printf("Cards were mismatched\n");
			fflush(stdout);
		}

		free(G);
		free(gCopy);

	}
		
		
	printf("Finished running %d tests\n", maxTests);	

	return 0;
}


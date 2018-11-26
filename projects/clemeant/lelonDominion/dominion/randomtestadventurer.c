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
	int temphand[500];
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			remodel, smithy, village, baron, great_hall};
	struct gameState* G; //= newGame();
	struct gameState* gCopy;// = newGame();
	//initializeGame(numPlayer, k, seed, G);
	
	printf("Random testing adventurer Card:\n");

	int i, maxTests, testNumPlayer, testHandSize, testDeckSize;
	maxTests = 10000;
	int* discards; 
	int* nonTreasureDeckCards;

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
		G->deck[chosenPlayer][0] = rand() % 3 + 4;	
		G->deck[chosenPlayer][1] = rand() % 3 + 4;
		G->deckCount[chosenPlayer] = testDeckSize;	

		for(j = 0; j < testHandSize; j++){
			G->hand[chosenPlayer][j] = rand() % 25;
		}
		G->handCount[chosenPlayer] = testHandSize;
		int preHandTreasureCount, postHandTreasureCount;
		preHandTreasureCount = postHandTreasureCount = 0;
		for(j = 0; j < G->handCount[chosenPlayer]; j++){
			if(G->hand[chosenPlayer][j] == copper || G->hand[chosenPlayer][j] == silver || G->hand[chosenPlayer][j] == gold){
				preHandTreasureCount++;
			}
		}
		
		int preHandCount = G->handCount[chosenPlayer];
		shuffle(chosenPlayer, G);
		G->discardCount[chosenPlayer] = 0;
		memcpy(gCopy, G, sizeof(struct gameState));
		adventurerCard(G, chosenPlayer, temphand);
		for(j = 0; j < G->handCount[chosenPlayer]; j++){
			if(G->hand[chosenPlayer][j] == copper || G->hand[chosenPlayer][j] == silver || G->hand[chosenPlayer][j] == gold){
				postHandTreasureCount++;
			}
		}

		int treasureCardCheck = 0;
		if(postHandTreasureCount != preHandTreasureCount + (G->handCount[chosenPlayer] - preHandCount)){
			printf("Treasure cards not added to hand correctly.\n");
			treasureCardCheck = 1;
		}
	
		discards = (int*)malloc(G->discardCount[chosenPlayer] * sizeof(int));

		int b;	
		for(b = 0; b < G->discardCount[chosenPlayer]; b++){
			discards[b] = G->discard[chosenPlayer][b];
		}

		nonTreasureDeckCards = (int*)malloc(G->discardCount[chosenPlayer] * sizeof(int));

		b = /*gCopy->deckCount[chosenPlayer] -*/ (G->discardCount[chosenPlayer] + 2);
		int insertIndex = 0;
		while(b != 0){
			int thisCard = 	gCopy->deck[chosenPlayer][gCopy->deckCount[chosenPlayer] - b];
			if(thisCard != copper && thisCard != silver && thisCard != gold){
				nonTreasureDeckCards[insertIndex] = gCopy->deck[chosenPlayer][gCopy->deckCount[chosenPlayer] - b];
				insertIndex++; 
			}
			b--;
		}
		
		int mismatchCount = 0;
		for(b = 0; b < G->discardCount[chosenPlayer]; b++){
			if(discards[b] != nonTreasureDeckCards[b]){
				mismatchCount++;
			}
		}
		
		if(mismatchCount != 0){
			printf("Cards in discard do not match cards drawn from deck\n");
			fflush(stdout);
		}

		if(treasureCardCheck == 1 || mismatchCount != 0){

			int a;
			printf("Pre Deck cards: \n");
			for (a = 0; a < testDeckSize; a++){
				printf("%d\n", gCopy->deck[chosenPlayer][a]);
			}
			
			printf("Pre Hand cards: \n");
			for (a = 0; a < testHandSize; a++){
				printf("%d\n", gCopy->hand[chosenPlayer][a]);
			}
			
			printf("Pre Discard cards: \n");
			for (a = 0; a < gCopy->discardCount[chosenPlayer]; a++){
				printf("%d\n", gCopy->discard[chosenPlayer][a]);
			}

		
			printf("Post Deck cards: \n");
			for (a = 0; a < G->deckCount[chosenPlayer]; a++){
				printf("%d\n", G->deck[chosenPlayer][a]);
			}
			
			printf("Post Hand cards: \n");
			for (a = 0; a < G->handCount[chosenPlayer]; a++){
				printf("%d\n", G->hand[chosenPlayer][a]);
			}
			
			printf("Post Discard cards: \n");
			for (a = 0; a < G->discardCount[chosenPlayer]; a++){
				printf("%d\n", G->discard[chosenPlayer][a]);
			}
		}
			
				
		free(discards);
		free(nonTreasureDeckCards);	
		free(G);	
		free(gCopy);
	}

	
	
	printf("Finished running %d tests\n", maxTests);
	fflush(stdout);

	return 0;
}


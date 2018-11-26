#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main(){
	
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			remodel, smithy, village, baron, great_hall};
	int temphand[MAX_HAND];
	struct gameState* G = newGame();

	initializeGame(numPlayer, k, seed, G);
	
	
	printf("Testing adventurer Card:\n");

	printf("Test 1: Adventurer card should result in player having two extra treasures in their hand\n");
	int preTreasureCount, preHandCount = 0;
	int i;
	for(i = 0; i < G->handCount[0]; i++){
		if(G->hand[0][i] == copper || G->hand[0][i] == silver || G->hand[0][i] == gold){
			preTreasureCount++;
		}
	}
	preHandCount = G->handCount[0];
	adventurerCard(G, 0, temphand);
	int postTreasureCount = 0;
	for(i = 0; i < G->handCount[0]; i++){
		if(G->hand[0][i] == copper || G->hand[0][i] == silver || G->hand[0][i] == gold){
			postTreasureCount++;
		}
	}

	if(postTreasureCount - 2 == preTreasureCount){
		printf("Test 1 PASSED\n");
	}
	else{
		printf("Test 1 FAILED\nHand contains %d extra treasures. 2 expected\n", postTreasureCount - preTreasureCount);
	}

	printf("Test 2: Only extra cards in hand should be treasures\n");

	if(G->handCount[0] == preHandCount + (postTreasureCount - preTreasureCount)){
		printf("Test 2 PASSED\n");
	}
	else{
		printf("Test 2 FAILED\nHand contains %d extra cards but only %d extra treasures\n", G->handCount[0] - preHandCount, postTreasureCount - preTreasureCount);
	}


	printf("Test 3: Drawn cards that are not treasure cards end up in discard pile\n");
	gainCard(8, G, 1, 0);	
	gainCard(9, G, 1, 0);
	gainCard(10, G, 1, 0);
	gainCard(11, G, 1, 0);
	gainCard(12, G, 1, 0);
	gainCard(13, G, 1, 0);
	gainCard(14, G, 1, 0);
	gainCard(15, G, 1, 0);
	gainCard(4, G, 1, 0);
	gainCard(5, G, 1, 0);
	gainCard(6, G, 1, 0);
	shuffle(0, G);
	shuffle(0, G);
	struct gameState* gCopy = newGame();
	memcpy(gCopy, G, sizeof(struct gameState));
	int preDeckCount = G->deckCount[0];
	//int preDiscardCount = G->discardCount[0];

	adventurerCard(G, 0, temphand);
	
	if(G->discardCount[0] == (preDeckCount - G->deckCount[0]) - 2){
		printf("Test 3 PASSED\n");
	}
	else{
		printf("Test 3 FAILED\nAmount of cards added to discard do not match number of cards removed from deck, not counting the two treasures\n");
	}

	printf("Test 4: The cards in the discard pile were the same cards drawn from the deck\n");

	int* discards = (int*)malloc(G->discardCount[0] * sizeof(int));
	
	for(i = 0; i < G->discardCount[0]; i++){
		discards[i] = G->discard[0][i];
	}

	int* nonTreasureDeckCards = (int*)malloc(G->discardCount[0] * sizeof(int));

	i = gCopy->deckCount[0] - (G->discardCount[0] + 2);
	int insertIndex = 0;
	while(i != 0){
		int thisCard = 	gCopy->deck[0][gCopy->deckCount[0] - i];
		if(thisCard != copper && thisCard != silver && thisCard != gold){
			nonTreasureDeckCards[insertIndex] = gCopy->deck[0][gCopy->deckCount[0] - i];
			insertIndex++; 
		}
		i--;
	}
	
	
	int errorCount = 0;
	for(i = 0; i < G->discardCount[0]; i++){
		if(discards[i] != nonTreasureDeckCards[i]){
			errorCount++;
		}
	}

	if(errorCount == 0){
		printf("Test 4 PASSED\n");
	}
	else{
		printf("Test 4 FAILED\nCards in discard do not match cards taken from deck\n");
	}


	free(discards);
	free(nonTreasureDeckCards);
	return 0;
}

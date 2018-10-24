#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			remodel, smithy, village, baron, great_hall};
	struct gameState* G = newGame();

	initializeGame(numPlayer, k, seed, G);
	
	
	printf("Testing smithy Card:\n");
	
	printf("Test 1: Smithy should draw three cards and add them to hand.\n");
	int preHandCount = G->handCount[0];
	smithyCardEffect(G, 0, 0);
	if(preHandCount + 2 == G->handCount[0]){
		printf("Test 1 PASSED\n");
	}
	else{
		printf("Test 1 FAILED\nSmithy card added %d cards to hand. 3 expected\n", G->handCount[0] - preHandCount + 1);
	}
	
	printf("Test 2: Deck is reduced by the number of cards drawn.\n");

	preHandCount = G->handCount[0];
	int preDeckCount = G->deckCount[0];
	smithyCardEffect(G, 0, 0);
	if(preDeckCount - G->deckCount[0] == G->handCount[0] - preHandCount + 1){
		printf("Test 2 PASSED\n");
	}
	else{
 		printf("Test 2 FAILED\nDeck reduced by %d and hand increased by %d\n", preDeckCount - G->deckCount[0], G->handCount[0] - preHandCount + 1);
	}
	
	printf("Test 3: Smithy card is put in play pile after being played\n");	
	G->hand[0][0] = smithy;
	smithyCardEffect(G, 0, 0);
	if(G->playedCards[G->playedCardCount - 1] == smithy){
		printf("Test 3 PASSED\n");
	}
	else{
		printf("Test 3 FAILED\nTop of played pile was not a smithy card\n");
	}

	printf("Test 4: Cards drawn come from top of deck\n");
	gainCard(8, G, 1, 0);
	gainCard(9, G, 1, 0);
	gainCard(10, G, 1, 0);
	gainCard(11, G, 1, 0);
	gainCard(12, G, 1, 0);
	gainCard(13, G, 1, 0);
	gainCard(14, G, 1, 0);
	gainCard(15, G, 1, 0);
	shuffle(0, G);
	struct gameState* gCopy = newGame();
	memcpy(gCopy, G, sizeof(struct gameState));
	preHandCount = G->handCount[0];
	smithyCardEffect(G, 0, 0);
	int i, errorCount = 0;
	for(i = 0; i < G->handCount[0] - preHandCount + 1; i++){
		if(G->hand[0][G->handCount[0] - 1 - i] != gCopy->deck[0][gCopy->deckCount[0] + 1 - (G->handCount[0] - preHandCount + 1) + i]){
			errorCount++;
		}
	}

	if(errorCount == 0){
		printf("Test 4 PASSED\n");
	}
	else{
		printf("Test 4 FAILED\nError count: %d\n", errorCount);
	}

	return 0;
}

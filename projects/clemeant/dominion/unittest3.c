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
	
	
	printf("Testing discardCard():\n");

	printf("Test 1: When trashing a card, card should not end up in played pile\n");
	int prePlayedCards = G->playedCardCount;
	int preHandCount = G->handCount[0];
	discardCard(0, 0, G, 1);
	assert(G->playedCardCount == prePlayedCards);
	printf("Test 1 PASSED\n");

	printf("Test 2: Function should reduce cards in hand by 1\n");
	assert(G->handCount[0] == (preHandCount - 1));
	printf("Test 2 PASSED\n");

	printf("Test 3: When not trashing card, card should end up in played pile\n");
	prePlayedCards = G->playedCardCount;
	int cardPlayed = G->hand[0][0];
	discardCard(0, 0, G, 0);
	assert(G->playedCardCount == (prePlayedCards + 1) && (G->playedCards[prePlayedCards] == cardPlayed));
	printf("Test 3 PASSED\n");

	initializeGame(numPlayer, k, seed, G);
	
	printf("Test 4: Discarding a whole hand should work properly for each card\n");
	int totalHandCount = G->handCount[0];
	int i;
	for(i = totalHandCount; i > 0; i--){
		if((0 == (G->handCount[0] - 1)) || i == 1){
			int handCount = G->handCount[0];
			discardCard(0, 0, G, 0);
			assert(G->handCount[0] == (handCount - 1));
		}
		else{
			int cardInSpot = G->hand[0][(G->handCount[0] - 1)];
			int handCount = G->handCount[0];
			discardCard(0, 0, G, 0);
			assert(G->hand[0][0] == cardInSpot);
			assert(G->hand[0][G->handCount[0]] = -1);
			assert(G->handCount[0] == (handCount -1));
		}
		
	}

	printf("Test 4 PASSED\n");


	return 0;
}

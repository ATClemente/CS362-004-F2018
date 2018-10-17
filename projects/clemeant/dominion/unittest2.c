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
	
	//int gainCard(int supplyPos (enum), struct gameState, int toFlag, int player);
	//toFlag = 0 discard
	//toflag = 1 deck
	//toFlag = 2 hand
	//returns -1 on failure
	
	
	printf("Testing gainCard():\n");

	printf("Test 1: Card not in game should fail\n");
	assert(gainCard(24, G, 1, 0) == -1);
	printf("Test 1 PASSED\n");

	printf("Test 2: Card in game but with empty supply pile should fail\n");
	G->supplyCount[0] = 0;
	assert(gainCard(0, G, 1, 0) == -1);
	printf("Test 2 PASSED\n");
	
	printf("Test 3: Card supply is reduced by 1 when that card is gained\n");
	G->supplyCount[0] = 2;
	gainCard(0, G, 1, 0);
	assert(G->supplyCount[0] == 1);
	gainCard(0, G, 1, 0);
	assert(G->supplyCount[0] == 0);
	printf("Test 3 PASSED\n");
	
	initializeGame(numPlayer, k, seed, G);
	
	printf("Test 4: toFlag works properly for discard\n");
	int preDiscardCount = G->discardCount[0];
	gainCard(0, G, 0, 0);
	assert(G->discardCount[0] == (preDiscardCount + 1));
	printf("Test 4 PASSED\n");

	
	printf("Test 5: toFlag works properly for deck\n");
	int preDeckCount = G->deckCount[0];
	gainCard(0, G, 1, 0);
	assert(G->deckCount[0] == (preDeckCount + 1));
	printf("Test 5 PASSED\n");
	

	printf("Test 6: toFlag works properly for hand\n");
	int preHandCount = G->handCount[0];
	gainCard(0, G, 2, 0);
	assert(G->handCount[0] == (preHandCount + 1));
	printf("Test 6 PASSED\n");
	
	initializeGame(numPlayer, k, seed, G);
	
	printf("Test 7: gainedCard ends up at proper space in discard\n");
	gainCard(0, G, 0, 0);
	assert(G->discard[0][G->discardCount[0] - 1] == 0);
	printf("Test 7 PASSED\n");	

	printf("Test 8: gainedCard ends up at proper space in deck\n");
	gainCard(0, G, 1, 0);
	assert(G->deck[0][G->deckCount[0] - 1] == 0);
	printf("Test 8 PASSED\n");	
	

	printf("Test 9: gainedCard ends up at proper space in hand\n");
	gainCard(0, G, 2, 0);
	assert(G->hand[0][G->handCount[0] - 1] == 0);
	printf("Test 9 PASSED\n");	
	
	return 0;
}

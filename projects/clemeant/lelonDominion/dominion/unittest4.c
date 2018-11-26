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
	
	//player deck starts with 3 estates and 7 coppers
	
	printf("Testing fullDeckCount():\n");

	printf("Test 1: Each player should start with 3 estates and 7 coppers\n");
	int i;
	for (i = 0; i < numPlayer; i++){
		assert(fullDeckCount(i, estate, G) == 3 && fullDeckCount(i, copper, G) == 7);
	}
	printf("Test 1 PASSED\n");

	printf("Test 2: Should count a card if it is in the discard\n");
	gainCard(smithy, G, 0, 0);
	assert(fullDeckCount(0, smithy, G) == 1);

	printf("Test 2 PASSED\n");
	
	printf("Test 3: Should count a card in the deck\n");
	gainCard(smithy, G, 1, 0);
	assert(fullDeckCount(0, smithy, G) == 2);

	printf("Test 3 PASSED\n");
	
	printf("Test 4: Should count a card in the hand\n");
	gainCard(smithy, G, 2, 0);
	assert(fullDeckCount(0, smithy, G) == 3);
	
	printf("Test 4 PASSED\n");

	printf("Test 5: Shuffling deck should not change results\n");
	int numShuffles = 10;
	printf("Check for %d shuffles\n", numShuffles);
	for(i = 0; i < numShuffles; i++){
		shuffle(0, G);
		assert(fullDeckCount(0, estate, G) == 3);
		assert(fullDeckCount(0, copper, G) == 7);
		assert(fullDeckCount(0, smithy, G) == 3);
	}
	
	printf("Test 5 PASSED\n");
	
	return 0;
}

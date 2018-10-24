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
	
	printf("Testing isGameOver():\n");
	
	printf("Test 1: Newly initialized game should not be over...\n");
	assert(isGameOver(G) == 0);
	printf("Test 1 PASSED\n");
	
	printf("Test 2: Empty province pile should result in game over\n");
	G->supplyCount[province] = 0;
	assert(isGameOver(G) == 1);
	printf("Test 2 PASSED\n");

	G->supplyCount[province] = 1;
	printf("Test 3: Three empty supply piles should end game.\n");
	int a, b, c, i;
	a = b = c = i = 0;
	int num_tests = 10;
	PutSeed(time(0));
	for (i = 0; i < num_tests; i++){
		while(a == b || a == c || b == c){
			a = Random() * 10.0;
			a %= 10;
			a += 7;
			b = Random() * 10.0;
			b %= 10;
			b += 7;
			c = Random() * 10.0;
			c %= 10;
			c += 7;
		}
		//printf("a, b, c: %d, %d, %d\n", a, b, c);
		G->supplyCount[a] = 0;
		G->supplyCount[b] = 0;
		G->supplyCount[c] = 0;
		assert(isGameOver(G) == 1);	
		G->supplyCount[a] = 1;
		G->supplyCount[b] = 1;
		G->supplyCount[c] = 1;
		assert(isGameOver(G) == 0);
		a = b = c = 0;
	}
	printf("Test 3 PASSED, %d iterations\n", num_tests);

	printf("Test 4: Empty supply piles of cards not in kingdom should not count\n");
	G->supplyCount[17] = 0;
	G->supplyCount[18] = 0;
	G->supplyCount[19] = 0;
	
	if(isGameOver(G) == 0){
		printf("Test 4 PASSED\n");
	}
	else{
		printf("Test 4 FAILED\n");
	}

	return 0;
}

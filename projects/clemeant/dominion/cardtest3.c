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
			remodel, smithy, village, baron, treasure_map};

	struct gameState* G = newGame();

	initializeGame(numPlayer, k, seed, G);
	
	printf("Testing treasure_map card:\n");

	printf("Test 1: Treasure map should return -1 if there is no other treasure map in the hand\n");
	gainCard(treasure_map, G, 2, 0);	
	assert(treasureMapCardEffect(G, 0, G->handCount[0] - 1) == -1);

	printf("Test 1 PASSED\n");
	
	gainCard(treasure_map, G, 2, 0);
	
	int* handCards = malloc((G->handCount[0] - 2) * sizeof(int));
	int i;
	int insertIndex = 0;
	for(i = 0; i < G->handCount[0] - 2; i++){
		if(G->hand[0][i] != treasure_map){
			handCards[insertIndex] = G->hand[0][i];
			insertIndex++;
		}
	}

	printf("Test 2: Treasure map should succeed if there are two treasure maps in the hand\n");
	//gainCard(treasure_map, G, 2, 0);
	int preGoldCount = fullDeckCount(0, gold, G);
	assert(treasureMapCardEffect(G, 0, G->handCount[0] - 1) == 1);
	
	printf("Test 2 PASSED\n");

	printf("Test 3: Upon treasure map success, player should have +4 golds than they did before\n");
	if(fullDeckCount(0, gold, G) == preGoldCount + 4){
		printf("Test 3 PASSED\n");
	}
	else{
		printf("Test 3 FAILED\nExpected %d golds. Actual: %d\n", preGoldCount + 4, fullDeckCount(0, gold, G));
	}

	printf("Test 4: Upon teasure map success, both treasure maps should be out of hand\n");
	int treasureMapHandCount = 0;
	for(i = 0; i < G->handCount[0]; i++){
		if(G->hand[0][i] == treasure_map){
			treasureMapHandCount++;
		}
	}
	
	if(treasureMapHandCount == 0){
		printf("Test 4 PASSED\n");
	}
	else{
		printf("Test 4 FAILED\nExpected treasure maps in hand is 0, was %d\n", treasureMapHandCount);
	}

	printf("Test 5: Upon success top 4 cards of deck should be gold cards\n");
	int errorCount = 0;
	for(i = 1; i <= 4; i++){
		if(G->deck[0][G->deckCount[0] - i] != gold){
			errorCount++;
		}
	}
	
	if(errorCount == 0){
		printf("Test 5 PASSED\n");
	}else{
		printf("Test 5 FAILED\nTop 4 cards on deck were not gold\n");
	}

	printf("Test 6: Cards in hand are same as before minus the treasure maps\n");

	errorCount = 0;

	for(i = 0; i < G->handCount[0]; i++){
		if(G->hand[0][i] != handCards[i]){
			errorCount++;
		}
	}

	if(errorCount == 0){
		printf("Test 6 PASSED\n");
	}
	else{
		printf("Test 6 FAILED\nCards do not match\n");
	}

	return 0;
}

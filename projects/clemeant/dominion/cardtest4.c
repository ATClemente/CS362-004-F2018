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
			remodel, smithy, village, baron, salvager};

	struct gameState* G = newGame();

	initializeGame(numPlayer, k, seed, G);
	
	printf("Testing salvager card:\n");

	printf("Test 1: Salvager card should increase number of buys by one\n");
	gainCard(salvager, G, 2, 0);
	int preBuys = G->numBuys;
	salvagerCardEffect(G, 0, G->handCount[0] - 1, 0);

	if(G->numBuys == preBuys + 1){
		printf("Test 1 PASSED\n");
	}
	else{
		printf("Test 1 FAILED\nExpected %d, actual %d\n", preBuys + 1, G->numBuys);
	}
	
	initializeGame(numPlayer, k, seed, G);
	gainCard(salvager, G, 2, 0);
	printf("Test 2: Salvager card should not increase coins if choice parameter is negative\n");	
	int preCoins = G->coins;	
	salvagerCardEffect(G, 0, G->handCount[0] - 1, -1);

	if(preCoins == G->coins){
		printf("Test 2 PASSED\n");
	}
	else{
		printf("Test 2 FAILED\nExpected %d coins, actual %d\n", preCoins, G->coins);
	}

	
	initializeGame(numPlayer, k, seed, G);
	gainCard(salvager, G, 2, 0);
	printf("Test 3: Salvager card should increase coins if first card in hand is chosen\n");	
	preCoins = G->coins;
	G->hand[0][0] = gold;	
	salvagerCardEffect(G, 0, G->handCount[0] - 1, 0);

	if(preCoins + getCost(gold) == G->coins){
		printf("Test 3 PASSED\n");
	}
	else{
		printf("Test 3 FAILED\nExpected %d coins, actual %d\n", preCoins + getCost(handCard(0, G)), G->coins);
	}

	initializeGame(numPlayer, k, seed, G);
	gainCard(salvager, G, 2, 0);
	printf("Test 4: Salvager card should increase coins if a valid positive index in hand is chosen\n");	
	preCoins = G->coins;
	G->hand[0][1] = gold;	
	salvagerCardEffect(G, 0, G->handCount[0] - 1, 1);

	if(preCoins + getCost(gold) == G->coins){
		printf("Test 4 PASSED\n");
	}
	else{
		printf("Test 4 FAILED\nExpected %d coins, actual %d\n", preCoins + getCost(handCard(0, G)), G->coins);
	}

	
	initializeGame(numPlayer, k, seed, G);
	gainCard(salvager, G, 2, 0);

	printf("Test 5: Both the Salvager card and card chosen should not be in hand if successful\n");	
	preCoins = G->coins;
	G->hand[0][1] = gold;	
	salvagerCardEffect(G, 0, G->handCount[0] - 1, 1);
	
	int errorCount = 0;
	int i;
	for(i = 0; i < G->handCount[0]; i++){
		if(G->hand[0][i] == gold || G->hand[0][i] == salvager){
			errorCount++;
		}
	}

	if(errorCount == 0){
		printf("Test 5 PASSED\n");
	}
	else{
		printf("Test 5 FAILED\n");
	}

	printf("Test 6: After playing, Salvager card should end up in played pile\n");

	initializeGame(numPlayer, k, seed, G);
	gainCard(salvager, G, 2, 0);	
	salvagerCardEffect(G, 0, G->handCount[0] - 1, 1);
	int salvCount = 0;
	for(i = 0; i < G->playedCardCount; i++){
		if(G->playedCards[i] == salvager){
			salvCount++;
		}
	}
	
	if(salvCount == 1){
		printf("Test 6 PASSED\n");
	}
	else{
		printf("Test 6 FAILED\nExpected %d salvager cards, actual %d\n", 1, salvCount);
	}

	return 0;
}

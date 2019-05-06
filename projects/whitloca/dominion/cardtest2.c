/*
cardtest2.c
Unittest for adventurer

include:

cardtest2: cardtest2.c dominion.o rngs.o
gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

in the makefile
*/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "adventurer"

int SUCCESS = 0;

//Custom Assert Function So The Program Doesn't Crash, Allows All Coverage To Be Found In The Case An Assert Fails
void customAssert(int varOne, int varTwo) {
	if (varOne != varTwo) {
		printf("**Assertion Failed** Program will continue instead of crashing\n", varOne, varTwo);
		SUCCESS = SUCCESS + 1;
	}
}

int main() {
	//Initialize needed variables for testing
	int x;
	int seed = 500;
	int players = 2;
	
	int cardsPlayed = 1;
	int cardsDrawn = 2;
	
	//Create game state
	struct gameState state, testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	
	int currentPlayer = whoseTurn(&state);
	
	//initialize base game, used to compare test results to
	initializeGame(players, k, seed, &state);
	
	//begin testing procedures
	printf("-------------------- Testing Card: %s --------------------\n", TESTCARD);
	
	//first test: the function ran successfully
	printf("TEST 1: Function Adventurer runs successfully\n");
	
	//initialize test gamestate
	initializeGame(players, k, seed, &testState);
	
	x = cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);
	
	customAssert(x, 0);
	printf("Card ran successfully\n");
	

	printf("TEST 2: Testing Result of %s Card\n", TESTCARD);
	printf("Hand Count = %d, Expected Hand Count = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn);
	customAssert(testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn);
	printf("Played Card Pile Count = %d, Expected Played Card Pile Count = %d\n", testState.playedCardCount, state.playedCardCount + cardsPlayed);
	customAssert(testState.playedCardCount, state.playedCardCount + cardsPlayed);
	int testPurchase = buyCard(adventurer, &testState);
	int purchase = buyCard(adventurer, &state);
	printf("Coin Count = %d, Expected Coin Count = %d\n", testPurchase, purchase);
	customAssert(testPurchase, purchase);


	
	if (SUCCESS == 0)
	printf("-------------------- SUCCESS: Testing for %s Complete --------------------\n\n", TESTCARD);
	if (SUCCESS != 0)
	printf("-------------------- TESTING FAILED: Failed %d Asserts --------------------\n\n", SUCCESS);
	return 0;
}
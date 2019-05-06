/*
cardtest4.c
Unittest for baron

include:

cardtest4: cardtest4.c dominion.o rngs.o
gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

in the makefile
*/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "baron"

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
	
	int gainedBuys = 1;
	int cardsDiscarded = 1;
	int gainedCoins = 4;
	
	//Create game state
	struct gameState state, testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	
	int currentPlayer = whoseTurn(&state);
	
	//initialize base game, used to compare test results to
	initializeGame(players, k, seed, &state);
	
	//begin testing procedures
	printf("-------------------- Testing Card: %s --------------------\n", TESTCARD);
	
	//first test: the function ran successfully
	printf("TEST 1: Baron runs successfully\n");
	
	//initialize test gamestate
	initializeGame(players, k, seed, &testState);
	
	x = cardEffect(baron, 2, 0, 0, &testState, 0, 0);
	
	customAssert(x, 0);
	printf("Card ran successfully\n");
	

	printf("TEST 2: Testing Result of %s Card, Discarding an Estate\n", TESTCARD);
	printf("Buy Count = %d, Expected Buy Count = %d\n", testState.numBuys, state.numBuys + gainedBuys);
	customAssert(testState.numBuys, state.numBuys + gainedBuys);
	printf("Hand Count = %d, Expected Hand Count = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] - cardsDiscarded);
	customAssert(testState.handCount[currentPlayer], state.handCount[currentPlayer] - cardsDiscarded);
	printf("Coin Count = %d, Expected Coin Count = %d\n", testState.coins, state.coins + gainedCoins);
	customAssert(testState.coins, state.coins + gainedCoins);
	printf("Cards Discarded from Hand = %d, Expected Cards Discarded from Hand = %d\n", testState.discardCount[currentPlayer], state.discardCount[currentPlayer] + cardsDiscarded);
	customAssert(testState.discardCount[currentPlayer], state.discardCount[currentPlayer] + cardsDiscarded);
	
	printf("TEST 3: Testing Result of %s Card, Discarding a Copper\n", TESTCARD);
	struct gameState testState2;
	initializeGame(players, k, seed, &testState2);
	x = cardEffect(baron, 0, 0, 0, &testState2, 1, 0);
	printf("Buy Count = %d, Expected Buy Count = %d\n", testState2.numBuys, state.numBuys + gainedBuys);
	customAssert(testState2.numBuys, state.numBuys + gainedBuys);
	printf("Hand Count = %d, Expected Hand Count = %d\n", testState2.handCount[currentPlayer], state.handCount[currentPlayer]);
	customAssert(testState2.handCount[currentPlayer], state.handCount[currentPlayer]);
	printf("Coin Count = %d, Expected Coin Count = %d\n", testState.coins, state.coins + gainedCoins);
	customAssert(testState.coins, state.coins + gainedCoins);


	
	if (SUCCESS == 0)
	printf("-------------------- SUCCESS: Testing for %s Complete --------------------\n\n", TESTCARD);
	if (SUCCESS != 0)
	printf("-------------------- TESTING FAILED: Failed %d Asserts --------------------\n\n", SUCCESS);
	return 0;
}
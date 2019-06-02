/*
cardtest3.c
Unittest for salvager

include:

cardtest3: cardtest3.c dominion.o rngs.o
gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

in the makefile
*/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "salvager"

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
	int gainedBuys = 1;
	int gainedTreasure = getCost(estate);
	
	//Create game state
	struct gameState state, testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	
	int currentPlayer = whoseTurn(&state);
	
	//initialize base game, used to compare test results to
	initializeGame(players, k, seed, &state);
	
	//begin testing procedures
	printf("-------------------- Testing Card: %s --------------------\n", TESTCARD);
	
	//first test: the function ran successfully
	printf("TEST 1: Function Salvager runs successfully\n");
	
	//initialize test gamestate
	initializeGame(players, k, seed, &testState);
	
	int trashedCard = testState.hand[currentPlayer][2];
	x = cardEffect(salvager, 2, 0, 0, &testState, 0, 0);
	
	customAssert(x, 0);
	printf("Card ran successfully\n");
	

	printf("TEST 2: Testing Result of %s Card\n", TESTCARD);
	printf("Trashed Card = %d, Expected Trashed Card = %d\n", trashedCard, state.hand[currentPlayer][2]);
	customAssert(trashedCard, state.hand[currentPlayer][2]);
	printf("Buys For This Turn = %d, Expected Buys For This Turn = %d\n", testState.numBuys, state.numBuys + gainedBuys);
	customAssert(testState.numBuys, state.numBuys + gainedBuys);
	printf("Coins Available = %d, Expected Coins Available = %d\n", testState.coins, state.coins + gainedTreasure);
	customAssert(testState.coins, state.coins + gainedTreasure);
	printf("Trashed Pile Count = %d, Expected Trashed Pile Count = %d\n", testState.playedCardCount, state.playedCardCount + cardsPlayed);	
	customAssert(testState.playedCardCount, state.playedCardCount + cardsPlayed);



	
	if (SUCCESS == 0)
	printf("-------------------- SUCCESS: Testing for %s Complete --------------------\n\n", TESTCARD);
	if (SUCCESS != 0)
	printf("-------------------- TESTING FAILED: Failed %d Asserts --------------------\n\n", SUCCESS);
	return 0;
}
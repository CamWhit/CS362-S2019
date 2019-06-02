/*
cardtest1.c
Unittest for smithy

include:

cardtest1: cardtest1.c dominion.o rngs.o
gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

in the makefile
*/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "smithy"

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
	
	//The smithy card is discarded after being played
	int cardsPlayed = 1;
	//Three cards should be drawn
	int drawnCards = 3;
	
	//Create game state
	struct gameState state, testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	
	int currentPlayer = whoseTurn(&state);
	
	//initialize base game, used to compare test results to
	initializeGame(players, k, seed, &state);
	
	//begin testing procedures
	printf("-------------------- Testing Card: %s --------------------\n", TESTCARD);
	
	//first test: the function ran successfully
	printf("TEST 1: Smithy runs successfully\n");
	
	//initialize test gamestate
	initializeGame(players, k, seed, &testState);
	
	x = cardEffect(smithy, 0, 0, 0, &testState, 0, 0);
	
	customAssert(x, 0);
	printf("Card ran successfully\n");
	
	//second test: the correct number of cards were drawn (3 cards should've been draw)
	printf("TEST 2: Testing Result of %s Card\n", TESTCARD);
	printf("Card Count = %d, Expected Card Count = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] + drawnCards - cardsPlayed);
	customAssert(testState.handCount[currentPlayer], state.handCount[currentPlayer] + drawnCards - cardsPlayed);
	printf("First Card in Hand = %d, Expected First Card in Hand = %d\n", testState.hand[currentPlayer][0], state.hand[currentPlayer][0]);
	customAssert(testState.hand[currentPlayer][0], state.hand[currentPlayer][0]);
	printf("Estate's in Starting Deck Count = %d, Expected Estate's in Starting Deck = %d\n", fullDeckCount(currentPlayer, estate, &testState), fullDeckCount(currentPlayer, estate, &state));
	customAssert(fullDeckCount(currentPlayer, estate, &testState), fullDeckCount(currentPlayer, estate, &state));

	
	if (SUCCESS == 0)
	printf("-------------------- SUCCESS: Testing for %s Complete --------------------\n\n", TESTCARD);
	if (SUCCESS != 0)
	printf("-------------------- TESTING FAILED: Failed %d Asserts --------------------\n\n", SUCCESS);
	return 0;
}
/*
unittest2.c
Unittest for refactored function adventurerCard

include:

unittest2: unittest2.c dominion.o rngs.o
gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

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
	int x;
	int handPos = 0;
	int seed = 500;
	int players = 2;
	
	//Comparison variables
	int cardsDiscard = 0;
	int cardsPlayed = 1;
	int cardsDrawn = 2;
	int drawTreasureCount = 0;
	int treasureCount = 0;
	
	struct gameState state, testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
		
	int currentPlayer = whoseTurn(&state);
	
	//Initialize comparison game state
	initializeGame(players, k, seed, &state);
	
	//begin testing procedures
	printf("-------------------- Testing Card: %s --------------------\n", TESTCARD);
	
	//Initialize testing game state
	initializeGame(players, k, seed, &testState);
	
	//Test to see if refactored function ran successfully
	printf("TEST 1: Function adventurerCard runs successfully\n");
	x = adventurerCard(&testState, currentPlayer, handPos);
	customAssert(x, 0);
	printf("Refactored function ran successfully\n");
	
	
	printf("TEST 2: Testing Result of %s Card\n", TESTCARD);
	printf("Hand Count = %d, Expected Hand Count = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn);
	customAssert(testState.handCount[currentPlayer], state.handCount[currentPlayer] + cardsDrawn);
	printf("Deck Count = %d, Expected Deck Count = %d\n", testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - cardsDrawn);
	customAssert(testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - cardsDrawn);
	printf("Played Card Pile Count = %d, Expected Played Card Pile Count = %d\n", testState.playedCardCount, state.playedCardCount + cardsPlayed);
	customAssert(testState.playedCardCount, state.playedCardCount + cardsPlayed);
	printf("Deck Count = %d, Expected Deck Count = %d\n", fullDeckCount(currentPlayer, copper, &testState), fullDeckCount(currentPlayer, copper, &state));
	customAssert(fullDeckCount(currentPlayer, copper, &testState), fullDeckCount(currentPlayer, copper, &state));
	printf("Value of two recent cards in hand: %d, %d\n", testState.hand[currentPlayer][5], testState.hand[currentPlayer][6]);
	customAssert(copper, testState.hand[currentPlayer][5]);
	customAssert(copper, testState.hand[currentPlayer][6]);
	
	if (SUCCESS == 0)
	printf("-------------------- SUCCESS: Testing for %s Complete --------------------\n", TESTCARD);
	if (SUCCESS != 0)
	printf("-------------------- TESTING FAILED: Failed %d Asserts --------------------\n", SUCCESS);
	return 0;
}
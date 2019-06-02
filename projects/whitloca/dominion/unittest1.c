/*
unittest1.c
Unittest for refactored function smithyCard

include:

unittest1: unittest1.c dominion.o rngs.o
gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

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
	int handPos = 0;
	int seed = 500;
	int players = 2;
	
	//The smithy card is discarded after being played
	int cardsDiscard = 1;
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
	printf("TEST 1: Function smithyCard runs successfully\n");
	
	//initialize test gamestate
	initializeGame(players, k, seed, &testState);
	
	
	x = smithyEffect(&testState, handPos, currentPlayer);
	customAssert(x, 0);
	printf("Refactored function ran successfully\n");
	
	//second test: the correct number of cards were drawn (3 cards should've been draw)
	printf("TEST 2: Testing Result of %s Card\n", TESTCARD);
	printf("Hand Count = %d, Expected Hand Count = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] + drawnCards - cardsDiscard);
	customAssert(testState.handCount[currentPlayer], state.handCount[currentPlayer] + drawnCards - cardsDiscard);
	printf("Deck Count = %d, Expected Deck Count = %d\n", testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - drawnCards);
	customAssert(testState.deckCount[currentPlayer], state.deckCount[currentPlayer] - drawnCards);
	printf("Opponent Hand Count = %d, Expected Opponent Hand Count = %d\n", testState.handCount[currentPlayer+1], state.handCount[currentPlayer+1]);
	customAssert(testState.handCount[currentPlayer+1], state.handCount[currentPlayer+1]);
	printf("Opponent Deck Count = %d, Expected Opponent Deck Count = %d\n", testState.deckCount[currentPlayer+1], state.deckCount[currentPlayer+1]);
	customAssert(testState.deckCount[currentPlayer+1], state.deckCount[currentPlayer+1]);
	printf("Played Card Pile Count = %d, Expected Played Card Pile Count = %d\n", testState.playedCardCount, state.playedCardCount + cardsDiscard);
	customAssert(testState.playedCardCount, state.playedCardCount + cardsDiscard);
	
	if (SUCCESS == 0)
		printf("-------------------- SUCCESS: Testing for %s Complete --------------------\n\n", TESTCARD);
	if (SUCCESS != 0)
		printf("-------------------- TESTING FAILED: Failed %d Asserts --------------------\n\n", SUCCESS);
	return 0;
}
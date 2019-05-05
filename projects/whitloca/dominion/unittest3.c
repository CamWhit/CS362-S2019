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

#define TESTCARD "minion"

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

	int cardsDiscard = 0;
	int drawnCards = 0;
	int playedCards = 1;
	int coinsGained = 2;

	//Create game state
	struct gameState state, testState;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room };


	int currentPlayer = whoseTurn(&state);

	//initialize base game, used to compare test results to
	initializeGame(players, k, seed, &state);

	//begin testing procedures
	printf("-------------------- Testing Card: %s --------------------\n", TESTCARD);

	//first test: the function ran successfully
	printf("TEST 1: Function minionCard runs successfully\n");

	//initialize test gamestate
	initializeGame(players, k, seed, &testState);
	int choice1 = 1;
	int choice2 = 0;

	x = minionCard(&testState, currentPlayer, handPos, choice1, choice2);
	customAssert(x, 0);
	printf("Refactored function ran successfully\n");


	printf("TEST 2: Testing Result of %s Card, choice 1 coins+2\n", TESTCARD);
	printf("Hand Count = %d, Expected Hand Count = %d\n", testState.handCount[currentPlayer], state.handCount[currentPlayer] - playedCards);
	customAssert(testState.handCount[currentPlayer], state.handCount[currentPlayer] - playedCards);
	printf("Coin Count = %d, Expected Coin Count = %d\n", testState.coins, state.coins + coinsGained);
	customAssert(testState.coins, state.coins + coinsGained);
	printf("Deck Count = %d, Expected Deck Count = %d\n", fullDeckCount(currentPlayer, minion, &testState) + 1, fullDeckCount(currentPlayer, minion, &state) + 1);
	customAssert(fullDeckCount(currentPlayer, minion, &testState) + 1, fullDeckCount(currentPlayer, minion, &state) + 1);
	printf("Number of actions = %d, Expected Number of actions = %d\n", testState.numActions, state.numActions + 1);
	customAssert(testState.numActions, state.numActions + 1);


	printf("TEST 3: Testing Result of %s Card, choice 2 players redraw to 4 cards\n", TESTCARD);
	struct gameState testState2;
	initializeGame(players, k, seed, &testState2);
	choice1 = 0;
	choice2 = 1;
	x = minionCard(&testState2, currentPlayer, handPos, choice1, choice2);
	printf("Hand Count = %d, Expected Hand Count = %d\n", testState2.handCount[currentPlayer], state.handCount[currentPlayer] - 1);
	customAssert(testState2.handCount[currentPlayer], state.handCount[currentPlayer] - 1);
	printf("Coin count = %d, Expected Coin Count = %d\n", testState2.coins, state.coins);
	customAssert(testState2.coins, state.coins);
	printf("Discard Count = %d, Expected Discard Count = %d\n", testState2.playedCardCount, state.playedCardCount + 4);
	customAssert(testState2.playedCardCount, state.playedCardCount + 4);
	printf("Number of actions = %d, Expected Number of actions = %d\n", testState2.numActions, state.numActions + 1);
	customAssert(testState2.numActions, state.numActions + 1);
	

	if (SUCCESS == 0)
		printf("-------------------- SUCCESS: Testing for %s Complete --------------------\n", TESTCARD);
	if (SUCCESS != 0)
		printf("-------------------- TESTING FAILED: Failed %d Asserts --------------------\n", SUCCESS);
	return 0;
}
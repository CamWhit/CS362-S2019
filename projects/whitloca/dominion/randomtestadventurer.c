/*
randomtestadventurer.c
Random Testing for the Refactored Adventurer Card Code

Include the Following in the Makefile:
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)


*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TESTCARD "Adventurer"

int FAILURES = 0;
int NUMTESTS = 2;

void customAssert(int varOne, int varTwo, int type) {
	if (varOne != varTwo) {
		if (type == 0)
			printf("**Assertion Failed** Function Failed To Run. Program will continue instead of crashing\n");
		else if (type == 1)
			printf("**Assertion Failed** Incorrect Draw Amount. Program will continue instead of crashing\n");
		else if (type == 2)
			printf("**Assertion Failed** Incorrect Played Card Count. Program will continue instead of crashing\n");
		else
			printf("**Assertion Failed** Program will continue instead of crashing\n");
		FAILURES = FAILURES + 1;
	}
}

//Main to random test adventurerCard()
int main() {
	//Setup variables needed to randomize an initial game state
	int numPlayers, currentPlayer;
	int k[10];
	int card;
	int added;
	int x;
	struct gameState testState, state;
	SelectStream(2);
	PutSeed(3);
	
	//Random testing loop
	for (int i = 0; i < NUMTESTS; i++) {	
		//Randomize initial game state
		numPlayers = 0;
		for (int j = 0; j < 10; j++) {
			k[j] = 0;
		}
		
		//Randomize starting player count
		numPlayers = floor((Random() * (MAX_PLAYERS/2))) + 2;
		
		//Randomize supply list
		for (int j = 0; j < 10; j++) {
			//27 different cards in the enum (8-27 cards)
			added = 1;
			while(added == 1)
			{
				added = 0;
				card = floor(Random() * 20)+ 7;
				for (int q = 0; q < 10; q++) {
					if (card == k[q])
						added = 1;
				}
			}
			k[j] = card;
		}
		
		for (int l = 0; l < sizeof(struct gameState); l++) {
			((char*) &testState)[l] = floor(Random() * 256);
			((char*) &state)[l] = ((char*) &testState)[l];
		}
		
		currentPlayer = floor(Random() * numPlayers);
		
		testState.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		state.deckCount[currentPlayer] = testState.deckCount[currentPlayer];
		
		if (testState.deckCount[currentPlayer] > 1) {
			testState.deck[currentPlayer][testState.deckCount[currentPlayer] - 1] = copper;
			testState.deck[currentPlayer][testState.deckCount[currentPlayer] - 2] = copper;
			state.deck[currentPlayer][state.deckCount[currentPlayer] - 1] = copper;
			state.deck[currentPlayer][state.deckCount[currentPlayer] - 2] = copper;
		} else {
			testState.deckCount[currentPlayer] = 2;
			testState.deck[currentPlayer][0] = copper;
			testState.deck[currentPlayer][1] = copper;
			state.deckCount[currentPlayer] = 2;
			state.deck[currentPlayer][0] = copper;
			state.deck[currentPlayer][1] = copper;
		}
		
		testState.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		state.discardCount[currentPlayer] = testState.discardCount[currentPlayer];
		if (testState.discardCount[currentPlayer] > 1) {
			testState.discard[currentPlayer][0] = copper;
			testState.discard[currentPlayer][1] = copper;
			state.discard[currentPlayer][0] = copper;
			state.discard[currentPlayer][1] = copper;
		} else {
			testState.discardCount[currentPlayer] = 2;
			testState.discard[currentPlayer][0] = copper;
			testState.discard[currentPlayer][1] = copper;
			state.discardCount[currentPlayer] = 2;
			state.discard[currentPlayer][0] = copper;
			state.discard[currentPlayer][1] = copper;
		}
		
		testState.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		state.handCount[currentPlayer] = testState.handCount[currentPlayer];
		
		//Statement used for testing
		printf("%d, %d, %d, %d, %d\n", numPlayers, currentPlayer, testState.deckCount[currentPlayer], testState.discardCount[currentPlayer], testState.handCount[currentPlayer]);
		
		x = adventurerEffect(&testState, currentPlayer);
		customAssert(x, 0, 0);
		//Statement used for testing
		printf("Ran statement\n");
		
		customAssert(testState.handCount[currentPlayer], state.handCount[currentPlayer] + 2, 1);
		customAssert(testState.playedCardCount, state.playedCardCount, 2);
		
	}
	
	
	
	//Exit Case
	if (FAILURES == 0)
	{
		printf("-------------------- SUCCESS: Testing for %s Complete --------------------\n\n", TESTCARD);
	} else {
		printf("-------------------- TESTING FAILED: Failed %d Asserts --------------------\n\n", FAILURES);
	}
	return 0;
}
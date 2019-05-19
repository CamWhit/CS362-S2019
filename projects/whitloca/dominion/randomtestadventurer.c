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
int NUMTESTS = 10000;

void customAssert(int varOne, int varTwo) {
	if (varOne != varTwo) {
		printf("**Assertion Failed** Program will continue instead of crashing\n", varOne, varTwo);
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
	int seed;
	struct gameState testState;
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
		}
		
		currentPlayer = floor(Random() * numPlayers);
		
		testState.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		if (testState.deckCount[currentPlayer] > 1) {
			testState.deck[currentPlayer][testState.deckCount[currentPlayer] - 1] = copper;
			testState.deck[currentPlayer][testState.deckCount[currentPlayer] - 2] = copper;
		} else {
			testState.deckCount[currentPlayer] = 2;
			testState.deck[currentPlayer][0] = copper;
			testState.deck[currentPlayer][1] = copper;
		}
		
		testState.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		if (testState.discardCount[currentPlayer] > 1) {
			testState.discard[currentPlayer][0] = copper;
			testState.discard[currentPlayer][1] = copper;
		} else {
			testState.discardCount[currentPlayer] = 2;
			testState.discard[currentPlayer][0] = copper;
			testState.discard[currentPlayer][1] = copper;
		}
		
		testState.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		
		//Statement used for testing
		//printf("%d, %d, %d, %d, %d\n", numPlayers, currentPlayer, testState.deckCount[currentPlayer], testState.discardCount[currentPlayer], testState.handCount[currentPlayer]);
		
		x = adventurerCard(&testState, currentPlayer);
		customAssert(x, 0);
		//Statement used for testing
		//printf("Ran statement\n");
		
		
		seed = floor(Random() * 500);
		initializeGame(numPlayers, k, seed, &testState);
		
		//initializeGame(); //Needs # players, supply list, seed, and state struct
		
		
		
		
		
		
		
		
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
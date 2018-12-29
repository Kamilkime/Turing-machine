#ifndef _TURING_H_IS_INCLUDED_
#define _TURING_H_IS_INCLUDED_

#include "list.h"

// A single turing machine state
typedef struct State {
    char *stateName;
    char conditionSymbol;
    char resultSymbol;
    char moveSymbol;
    char *nextStateName;
} State;

// Load a turing machine data from file
int loadTuring(FILE *inputFile, List *symbols, List *memoryTape, List *states, int *startIndex);

// Check the validity of the states
int checkStates(List *states);

// Get a state by name and condition symbol, or NULL if none was found
State *getState(char *stateName, char conditionSymbol, List *states);

// Executes a state and return next, or NULL if next is STOP
State *executeState(State *state, List *memoryTape, List *states, int *headIndex);

// Print the memory tape
void printTape(List *memoryTape, int headIndex);

#endif
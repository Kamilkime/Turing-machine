#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turing.h"
#include "turingLoader.h"

// Load a turing machine data from file
int loadTuring(FILE *inputFile, List *symbols, List *memoryTape, List *states, int *startIndex) {
    int symbolsLoaded = 0, tapeLoaded = 0, startIndexLoaded = 0;

    while (1) {
        char *line = readLine(inputFile);

        // EOF - stop the loop
        if (line[0] == EOF) {
            free(line);
            break;
        }

        // Skip empty line
        if (strlen(line) == 0) {
            free(line);
            continue;
        }

        // Load symbols line
        if (!symbolsLoaded) {
            loadSymbols(line, symbols);
            symbolsLoaded = 1;

            free(line);
            continue;
        }

        // Load tape line
        if (!tapeLoaded) {
            if (!loadTape(line, memoryTape, symbols)) {
                free(line);
                return 0;
            }

            tapeLoaded = 1;

            free(line);
            continue;
        }

        // Load start index line
        if (!startIndexLoaded) {
            if (!loadStartIndex(line, startIndex)) {
                free(line);
                return 0;
            }

            startIndexLoaded = 1;

            free(line);
            continue;
        }

        // Load state line
        if (!loadState(line, states, symbols)) {
            free(line);
            return 0;
        }

        free(line);
    }

    return 1;
}

// Check the validity of the states
int checkStates(List *states) {
    int startStateFound = 0, stopStateFound = 0, i = 0;

    for (; i < states -> items; i++) {
        State *state = getFromList(states, i);

        if (!strcmp(state -> stateName, "START")) {
            if (startStateFound) {
                printf("\nYou can only have one START state!\n\n");
                return 0;
            }

            startStateFound = 1;
        } else if (strcmp(state -> nextStateName, "STOP")) {
            stopStateFound = 1;
        }
    }

    if (!stopStateFound) {
        printf("\nYou must have at least one STOP result state!\n\n");
        return 0;
    }

    return 1;
}

// Get a state by name and condition symbol, or NULL if none was found
State *getState(char *stateName, char conditionSymbol, List *states) {
    int i = 0;
    for (; i < states -> items; i++) {
        State *state = getFromList(states, i);

        if (!strcmp(state -> stateName, stateName) && state -> conditionSymbol == conditionSymbol) {
            return state;
        }
    }

    printf("\nNo state found for name %s and condition %c!\n\n", stateName, conditionSymbol);
    return NULL;
}

// Executes a state and return next, or NULL if next is STOP
State *executeState(State *state, List *memoryTape, List *states, int *headIndex) {
    if (state == NULL) {
        return NULL;
    }

    // Print state execution
    printf("%s -----> %s (%c -> %c, moving %c)\n", state -> stateName, state -> nextStateName, state -> conditionSymbol, state -> resultSymbol, state -> moveSymbol);

    char *currentSymbol = getFromList(memoryTape, *headIndex);
    *currentSymbol = state -> resultSymbol;

    // Move memory reading head
    if (state -> moveSymbol == 'R') {
        (*headIndex)++;
    } else {
        (*headIndex)--;
    }

    // Next state is STOP - return NULL
    if (!strcmp(state -> nextStateName, "STOP")) {
        return NULL;
    }

    // Return next state
    return getState(state -> nextStateName, *((char*) getFromList(memoryTape, *headIndex)), states);
}

// Print the memory tape
void printTape(List *memoryTape, int headIndex) {
    int i = 0;
    for (; i < memoryTape -> items; i++) {
        printf("%c", *((char*) getFromList(memoryTape, i)));
    }

    printf("\n");
    for (i = 0; i < headIndex; i++) {
        printf(" ");
    }

    printf("^\n\n");
}
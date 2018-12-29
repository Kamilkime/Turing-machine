#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "turing.h"

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("\nCorrect usage: ./turing fileName\n\n");
        return 0;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("\nGiven file could not be found!\n\n");
        return 0;
    }

    List *symbols = initList(5);
    List *memoryTape = initList(10);
    List *states = initList(10);

    int headIndex = -1;

    if (!loadTuring(inputFile, symbols, memoryTape, states, &headIndex)) {
        return 0;
    }

    if (!checkStates(states)) {
        return 0;
    }

    printf("\nStarting tape:\n");
    printTape(memoryTape, headIndex);
    sleep(1);

    State *currentState = getState("START", *((char*) getFromList(memoryTape, headIndex)), states);
    while ((currentState = executeState(currentState, memoryTape, states, &headIndex)) != NULL) {
        printTape(memoryTape, headIndex);
        sleep(1);
    }

    printTape(memoryTape, headIndex);
}
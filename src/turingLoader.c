#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turing.h"
#include "turingLoader.h"

// Returns the next line from the file, or just EOF if the file has ended
char *readLine(FILE *inputFile) {
    char *line = malloc(8192 * sizeof(char));

    int currentIndex = 0;
    char temp;

    while ((temp = fgetc(inputFile)) != '\n') {
        line[currentIndex++] = temp;

        if (temp == EOF) {
            break;
        }
    }

    // If the last character of a valid line is an EOF char - ignore it for now
    if(currentIndex >= 2 && line[currentIndex - 1] == EOF) {
        currentIndex--;
    }

    // If the last character of a valid line is a CR or LF char - ignore it
    if (currentIndex >= 1 && (line[currentIndex - 1] == 13 || line[currentIndex - 1] == 10)) {
        currentIndex--;
    }

    line[currentIndex] = '\0';

    return line;
}

// Load symbols from the line
void loadSymbols(char *line, List *symbols) {
    int i = 0;
    for (; i < strlen(line); i++) {
        char *symbol = malloc(sizeof(char));
        *symbol = line[i];

        addToList(symbols, symbol);
    }
}

// Load memory tape from the line
int loadTape(char *line, List *memoryTape, List *symbols) {
    int i = 0;
    for (; i < strlen(line); i++) {
        if (!isValidSymbol(symbols, line[i])) {
            printf("\n%c is not a valid symbol!\n\n", line[i]);
            return 0;
        }

        char *tapePart = malloc(sizeof(char));
        *tapePart = line[i];

        addToList(memoryTape, tapePart);
    }

    return 1;
}

// Load start index from the line
int loadStartIndex(char *line, int *startIndex) {
    int i = 0;
    for (; i < strlen(line); i++) {
        if (line[i] != '^') {
            continue;
        }

        *startIndex = i;
        return 1;
    }

    printf("\nNo start position correctly specified!\n\n");
    return 0;
}

// Load machine state from the line
int loadState(char *line, List *states, List *symbols) {
    int i = 0;
    char buffer[8192];

    while (line[i] != ' ') {
        buffer[i] = line[i];
        i++;
    }

    buffer[i] = '\0';

    char *stateName = malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(stateName, buffer);

    if (!isValidSymbol(symbols, line[++i])) {
        printf("\n%c is not a valid symbol!\n\n", line[i]);
        return 0;
    }

    char conditionSymbol = line[i++];

    if (!isValidSymbol(symbols, line[++i])) {
        printf("\n%c is not a valid symbol!\n\n", line[i]);
        return 0;
    }

    char resultSymbol = line[i++];

    if (line[++i] != 'R' && line[i] != 'L') {
        printf("\n%c is not a valid move symbol!\n\n", line[i]);
        return 0;
    }

    char moveSymbol = line[i++];

    int nextStateStart = ++i;
    while (i < strlen(line)) {
        buffer[i - nextStateStart] = line[i];
        i++;
    }

    buffer[i - nextStateStart] = '\0';

    char *nextStateName = malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(nextStateName, buffer);

    State *state = malloc(sizeof(State));

    state -> stateName = stateName;
    state -> conditionSymbol = conditionSymbol;
    state -> resultSymbol = resultSymbol;
    state -> moveSymbol = moveSymbol;
    state -> nextStateName = nextStateName;

    addToList(states, state);

    return 1;
}

// Checks if the given character is a valid symbol (one of the defined symbols or a #)
int isValidSymbol(List *symbols, char c) {
    if (c != '#') {
        int i = 0;
        for (; i < symbols -> items; i++) {
            if (*((char*) getFromList(symbols, i)) == c) {
                return 1;
            }
        }

        return 0;
    }

    return 1;
}
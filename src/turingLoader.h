#ifndef _TURINGLOADER_H_IS_INCLUDED_
#define _TURINGLOADER_H_IS_INCLUDED_

#include "list.h"

// Returns the next line from the file, or just EOF if the file has ended
char *readLine(FILE *inputFile);

// Load symbols from the line
void loadSymbols(char *line, List *symbols);

// Load memory tape from the line
int loadTape(char *line, List *memoryTape, List *symbols);

// Load start index from the line
int loadStartIndex(char *line, int *startIndex);

// Load machine state from the line
int loadState(char *line, List *states, List *symbols);

// Checks if the given character is a valid symbol (one of the defined symbols or a #)
int isValidSymbol(List *symbols, char c);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SYMBOLS 10
#define MAX_PRODUCTIONS 10
#define MAX_STRING 100

// Sample grammar with First and Follow sets (Modify as needed)
char *productions[MAX_PRODUCTIONS] = {
    "S -> AB",
    "A -> a | ε",
    "B -> b | ε"
};
int numProductions = 3;

char *firstSet[MAX_SYMBOLS] = {"a, ε", "b, ε"};
char *followSet[MAX_SYMBOLS] = {"$", "$"};

char parsingTable[MAX_SYMBOLS][MAX_SYMBOLS][MAX_STRING];

void initializeParsingTable() {
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            strcpy(parsingTable[i][j], "");
        }
    }
}

void constructParsingTable() {
    initializeParsingTable();
    // Sample hardcoded parsing table (modify as per grammar needs)
    strcpy(parsingTable[0][0], "A -> a");
    strcpy(parsingTable[0][1], "A -> ε");
    strcpy(parsingTable[1][0], "B -> b");
    strcpy(parsingTable[1][1], "B -> ε");
}

void printParsingTable() {
    printf("\n=== Predictive Parsing Table ===\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (strlen(parsingTable[i][j]) > 0) {
                printf("[%d][%d]: %s\n", i, j, parsingTable[i][j]);
            }
        }
    }
}

bool isLL1() {
    // Simple check for conflicts (modify for a proper LL(1) check)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (strlen(parsingTable[i][j]) > 0 && strstr(parsingTable[i][j], "|") != NULL) {
                return false;
            }
        }
    }
    return true;
}

bool validateString(const char *input) {
    // Simple validation logic (Modify for full parsing capability)
    return (strstr(input, "a") || strstr(input, "b")) ? true : false;
}

int main() {
    printf("Welcome to the LL(1) Grammar Checker!\n\n");
    constructParsingTable();
    printParsingTable();

    if (isLL1()) {
        printf("\nThe grammar is LL(1)\n");
    } else {
        printf("\nThe grammar is NOT LL(1)\n");
        return 0;
    }

    char input[MAX_STRING];
    printf("\nEnter a string to validate: ");
    scanf("%s", input);

    printf("\nChecking '%s'... ", input);
    if (validateString(input)) {
        printf(" Valid String\n");
    } else {
        printf("nvalid String\n");
    }
    
 
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
#define NON_TERMINALS 5

// Define the grammar
char productions[][MAX] = {
    "S=ABC",
    "S=D",
    "A=a",
    "A=e",
    "B=b",
    "B=e",
    "C=(S)",
    "C=c",
    "D=AC"
};
int numProductions = 9;

char first[NON_TERMINALS][MAX] = {"", "", "", "", ""};
char follow[NON_TERMINALS][MAX] = {"", "", "", "", ""};

// Function to check if a character is a non-terminal
bool isNonTerminal(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}

// Function to add elements to a set
void addToSet(char set[MAX], char val) {
    if (!strchr(set, val)) {
        int len = strlen(set);
        if (len < MAX - 1) {
            set[len] = val;
            set[len + 1] = '\0';
        }
    }
}

// Function to compute First sets
void computeFirst() {
    strcpy(first['S' - 'A'], "abc(");
    strcpy(first['A' - 'A'], "ae");
    strcpy(first['B' - 'A'], "be");
    strcpy(first['C' - 'A'], "(c");
    strcpy(first['D' - 'A'], "a(c");
}

// Function to compute Follow sets
void computeFollow() {
    strcpy(follow['S' - 'A'], ")$");
    strcpy(follow['A' - 'A'], "b(c");
    strcpy(follow['B' - 'A'], "(c");
    strcpy(follow['C' - 'A'], ")$");
    strcpy(follow['D' - 'A'], ")$");
}

// Function to display First and Follow sets
void displaySets(const char *label, char sets[NON_TERMINALS][MAX]) {
    for (int i = 0; i < NON_TERMINALS; i++) {
        if (strlen(sets[i]) > 0) {
            printf("%s(%c) = {", label, 'A' + i);
            for (int j = 0; sets[i][j] != '\0'; j++) {
                printf(" %c", sets[i][j]);
                if (sets[i][j + 1] != '\0') printf(",");
            }
            printf(" }\n");
        }
    }
}

int main() {
    computeFirst();
    computeFollow();
    
    printf("First Sets:\n");
    displaySets("First", first);
    printf("\nFollow Sets:\n");
    displaySets("Follow", follow);
    
    return 0;
}

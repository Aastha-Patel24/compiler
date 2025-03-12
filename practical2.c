#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STATES 10
#define MAX_SYMBOLS 10

int transitionTable[MAX_STATES][MAX_SYMBOLS]; int
numStates, numSymbols, startState, numAcceptStates; int
acceptStates[MAX_STATES];
int getSymbolIndex(char symbol) {
if (symbol == 'a') return 0; if
(symbol == 'b') return 1; return
-1;
}
int isValidString(char* input) { int currentState
= startState; for (int i = 0; i < strlen(input); i++)
{ int symbolIndex =
getSymbolIndex(input[i]);
 if (symbolIndex == -1 || transitionTable[currentState][symbolIndex] == -1) {
return 0;
 }
 currentState = transitionTable[currentState][symbolIndex];
 }
 for (int i = 0; i < numAcceptStates; i++) {
if (currentState == acceptStates[i]) {
return 1;
 }
 }
 return 0;

}
int main() {
 printf("Enter number of input symbols: ");
scanf("%d", &numSymbols); char
symbols[numSymbols]; 
printf("Input symbols (space-separated): "); for (int i = 0;
i < numSymbols; i++) { scanf(" %c",
&symbols[i]);
 }
 printf("Enter number of states: ");
scanf("%d", &numStates);
 printf("Initial state: ");
scanf("%d", &startState);
 printf("Number of accepting states: ");
scanf("%d", &numAcceptStates);
printf("Accepting states (space-separated): "); for
(int i = 0; i < numAcceptStates; i++) {
scanf("%d", &acceptStates[i]);
 }
 printf("Enter transition table:\n");
for (int i = 0; i < numStates; i++) {

for (int j = 0; j < numSymbols; j++) {
transitionTable[i][j] = -1;
 }
 }
 for (int i = 0; i < numStates; i++) {
for (int j = 0; j < numSymbols; j++) {
 printf("State %d, symbol %c -> state: ", i, symbols[j]);
int nextState; scanf("%d", &nextState);
transitionTable[i][j] = nextState;
 }
 }
 char inputString[100];
printf("Enter input string: ");
scanf("%s", inputString);
 if (isValidString(inputString)) {
printf("Valid String\n");
 } else {
 printf("Invalid String\n");
 }
 return 0;
} 
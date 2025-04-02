#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR 100
#define MAX_QUADS 50

typedef struct {
    char op[3];      // Operator
    char arg1[10];   // First operand
    char arg2[10];   // Second operand
    char result[10]; // Result
} Quadruple;

Quadruple quads[MAX_QUADS]; // Array to store quadruples
int quadIndex = 0, tempVarCount = 1;

// Function to generate a new temporary variable name
void getTempVar(char *temp) {
    sprintf(temp, "t%d", tempVarCount++);
}

// Function to generate quadruple entry
void generateQuadruple(char *op, char *arg1, char *arg2, char *result) {
    strcpy(quads[quadIndex].op, op);
    strcpy(quads[quadIndex].arg1, arg1);
    strcpy(quads[quadIndex].arg2, arg2);
    strcpy(quads[quadIndex].result, result);
    quadIndex++;
}

// Function to process an arithmetic expression and generate quadruples
void processExpression(char *expr) {
    char stack[MAX_EXPR][10]; // Stack to store operands and temp variables
    int top = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {  // If the character is a digit
            char num[10] = "";
            int j = 0;
            while (isdigit(expr[i])) {
                num[j++] = expr[i++];
            }
            num[j] = '\0';
            strcpy(stack[++top], num);
            i--; // Adjust for loop increment
        } else if (strchr("+-*/", expr[i])) {  // If operator
            char op[2] = {expr[i], '\0'};
            char operand2[10], operand1[10], tempVar[10];

            // Pop operands
            strcpy(operand2, stack[top--]);
            strcpy(operand1, stack[top--]);

            // Generate temporary variable
            getTempVar(tempVar);
            
            // Generate quadruple
            generateQuadruple(op, operand1, operand2, tempVar);

            // Push result onto stack
            strcpy(stack[++top], tempVar);
        }
    }
}

// Function to print the quadruple table
void printQuadruples() {
    printf("\nGenerated Quadruple Table:\n");
    printf("%-10s %-10s %-10s %-10s\n", "Operator", "Operand 1", "Operand 2", "Result");
    for (int i = 0; i < quadIndex; i++) {
        printf("%-10s %-10s %-10s %-10s\n",
               quads[i].op,
               quads[i].arg1,
               quads[i].arg2,
               quads[i].result);
    }
}

int main() {
    char expr[MAX_EXPR];

    // Input arithmetic expression5 + 6 – 35 + 6 – 35 + 6 – 3
    printf("Enter an arithmetic expression: ");
    fgets(expr, MAX_EXPR, stdin);
    expr[strcspn(expr, "\n")] = 0; // Remove newline character

    // Process expression
    processExpression(expr);

    // Output quadruple table
    printQuadruples();

    return 0;
}

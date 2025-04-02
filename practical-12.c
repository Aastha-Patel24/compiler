#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_EXPR 100

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to evaluate an arithmetic expression with two numbers
int evaluate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 0; // Avoid division by zero
        default: return 0;
    }
}

// Function to optimize the expression using constant folding
void optimizeExpression(char *expr, char *optimized) {
    int i = 0, num1 = 0, num2 = 0, result;
    char op = '\0', temp[MAX_EXPR], var[MAX_EXPR] = "";
    int varIndex = 0, tempIndex = 0, hasVariable = 0;

    while (expr[i] != '\0') {
        if (isdigit(expr[i])) {
            temp[tempIndex++] = expr[i];
        } else if (isOperator(expr[i])) {
            temp[tempIndex] = '\0';
            if (op == '\0') {
                num1 = atoi(temp);
            } else {
                num2 = atoi(temp);
                num1 = evaluate(num1, num2, op);
            }
            op = expr[i];
            tempIndex = 0;
        } else if (isalpha(expr[i])) {
            hasVariable = 1;
            var[varIndex++] = expr[i];
        }
        i++;
    }

    // Last number evaluation
    if (tempIndex > 0) {
        temp[tempIndex] = '\0';
        num2 = atoi(temp);
        num1 = evaluate(num1, num2, op);
    }

    // Construct the optimized expression
    if (hasVariable) {
        sprintf(optimized, "%d %c %s", num1, op, var);
    } else {
        sprintf(optimized, "%d", num1);
    }
}

int main() {
    char expr[MAX_EXPR], optimized[MAX_EXPR];

    // Input arithmetic expressionxx
    printf("Enter an arithmetic expression: ");
    fgets(expr, MAX_EXPR, stdin);
    expr[strcspn(expr, "\n")] = 0; // Remove newline character

    // Optimize the expression
    optimizeExpression(expr, optimized);

    // Output optimized expression
    printf("Optimized Expression: %s\n", optimized);

    return 0;
}

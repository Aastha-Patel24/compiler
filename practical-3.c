#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LENGTH 100
#define MAX_SYMBOLS 100
#define MAX_ERRORS 100

// Keywords in C
const char *keywords[] = {"int", "char", "return", "void", "float", "long", "struct"};
int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

// Symbol Table
char symbol_table[MAX_SYMBOLS][MAX_IDENTIFIER_LENGTH];
int symbol_count = 0;

// Lexical Errors
char lexical_errors[MAX_ERRORS][MAX_IDENTIFIER_LENGTH];
int error_count = 0;

// Function to check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>');
}

// Function to check if a character is punctuation
int isPunctuation(char ch) {
    return (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}');
}

// Function to check if an identifier is valid
int isValidIdentifier(const char *identifier) {
    if (!isalpha(identifier[0]) && identifier[0] != '_') return 0;  // Must start with a letter or underscore
    for (int i = 1; identifier[i] != '\0'; i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '_') return 0;
    }
    return 1;
}

// Function to add identifier to symbol table
void addToSymbolTable(const char *identifier) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], identifier) == 0)
            return;
    }
    strcpy(symbol_table[symbol_count++], identifier);
}

// Function to add lexical error
void addLexicalError(const char *error) {
    strcpy(lexical_errors[error_count++], error);
}

// Function to process input from stdin
void processInput() {
    char ch, buffer[MAX_IDENTIFIER_LENGTH];
    int buffer_index = 0;
    int line_number = 1;
    int in_comment = 0;

    printf("Enter C code (end with EOF - Ctrl+D in Linux/macOS, Ctrl+Z in Windows):\n");

    while ((ch = getchar()) != EOF) {
        if (ch == '\n') line_number++;

        // Handling comments
        if (ch == '/' && (ch = getchar()) == '/') {
            while ((ch = getchar()) != '\n' && ch != EOF);
            line_number++;
            continue;
        }
        if (ch == '/' && (ch = getchar()) == '*') {
            in_comment = 1;
            while (in_comment) {
                if ((ch = getchar()) == '*') {
                    if ((ch = getchar()) == '/') in_comment = 0;
                }
                if (ch == '\n') line_number++;
            }
            continue;
        }

        // Tokenizing logic
        if (isalnum(ch) || ch == '_') {
            buffer[buffer_index++] = ch;
        } else {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                buffer_index = 0;

                if (isKeyword(buffer)) {
                    printf("Keyword: %s\n", buffer);
                } else if (isdigit(buffer[0])) {
                    int valid_constant = 1;
                    for (int i = 1; buffer[i] != '\0'; i++) {
                        if (!isdigit(buffer[i])) {
                            valid_constant = 0;
                            break;
                        }
                    }
                    if (valid_constant) {
                        printf("Constant: %s\n", buffer);
                    } else {
                        printf("Lexical Error (Line %d): %s is an invalid constant\n", line_number, buffer);
                        addLexicalError(buffer);
                    }
                } else if (isValidIdentifier(buffer)) {
                    printf("Identifier: %s\n", buffer);
                    addToSymbolTable(buffer);
                } else {
                    printf("Lexical Error (Line %d): %s is an invalid identifier\n", line_number, buffer);
                    addLexicalError(buffer);
                }
            }
            if (isOperator(ch)) {
                printf("Operator: %c\n", ch);
            } else if (isPunctuation(ch)) {
                printf("Punctuation: %c\n", ch);
            }
        }
    }
}

int main() {
    processInput();
    
    // Printing symbol table
    printf("\nSYMBOL TABLE:\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%d) %s\n", i + 1, symbol_table[i]);
    }

    // Printing lexical errors
    if (error_count > 0) {
        printf("\nLEXICAL ERRORS:\n");
        for (int i = 0; i < error_count; i++) {
            printf("%d) %s\n", i + 1, lexical_errors[i]);
        }
    } else {
        printf("\nNo Lexical Errors Found!\n");
    }

    return 0;
}

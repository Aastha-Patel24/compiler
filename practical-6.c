#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *input;
    int pos;
} Parser;

bool match(Parser *parser, char c) {
    if (parser->pos < strlen(parser->input) && parser->input[parser->pos] == c) {
        parser->pos++;
        return true;
    }
    return false;
}

bool S(Parser *parser);
bool L(Parser *parser);
bool L_prime(Parser *parser);

bool S(Parser *parser) {
    return match(parser, 'a') || (match(parser, '(') && L(parser) && match(parser, ')'));
}

bool L(Parser *parser) {
    return S(parser) && L_prime(parser);
}

bool L_prime(Parser *parser) {
    if (match(parser, ',')) {
        return S(parser) && L_prime(parser);
    }
    return true; // ε (empty case)
}

void parse(const char *input) {
    Parser parser = { strdup(input), 0 };  // Dynamic allocation
    int length = strlen(input);

    if (S(&parser) && parser.pos == length) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }

    free(parser.input);  // Free allocated memory
}

int main() {
    char input[256];  // Buffer for user input

    printf("Enter a string to parse: ");
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';  // Remove newline character
        parse(input);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}

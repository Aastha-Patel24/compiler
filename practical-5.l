%{
#include <stdio.h>
#include <stdlib.h>
%}
/* Regular definitions */
DIGIT [0-9]
LETTER [a-zA-Z_]
IDENTIFIER {LETTER}({LETTER}|{DIGIT})*
CONSTANT {DIGIT}+
STRING ".*"|'.'
WHITESPACE [ \t\n]+
COMMENT \/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/|\/\/.*
OPERATOR [=+\-*/%<>!&|^]
PUNCTUATION [(){};,]

/* Keywords */
KEYWORD
(int|char|return|if|else|while|for|do|switch|case|break|continue|void|float
|double|static|struct|typedef)
%%
{KEYWORD} { printf("Keyword: %s\n", yytext); }
{IDENTIFIER} { printf("Identifier: %s\n", yytext); }
{CONSTANT} { printf("Constant: %s\n", yytext); }
{STRING} { printf("String: %s\n", yytext); }
{PUNCTUATION} { printf("Punctuation: %s\n", yytext); }
{OPERATOR} { printf("Operator: %s\n", yytext); }
{COMMENT} { /* Ignore comments */ }
{WHITESPACE} { /* Ignore whitespace */ }
. { printf("Lexical Error: %s\n", yytext); }
%%
int main(int argc, char *argv[]) {
 if (argc > 1) {
 FILE *file = fopen(argv[1], "r");
 if (!file) {
 perror("Error opening file");
 return 1;
 }
 yyin = file;
 printf("File opened successfully: %s\n", argv[1]);
 } else {

 printf("No input file provided.\n");
 return 1;
 }
 yylex();
 return 0;
}
int yywrap() {
 return 1;
}
/*4.1*/
%{
#include <stdio.h>
%}

%%
[0-9]+          { printf("%s\n", yytext); }
[ \t\n]         ;  
.              ; /* Ignore other characters */
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}


/*4.2*/

%{
#include <stdio.h>
#include <string.h>
%}

%%
charusat        { printf("university"); }
.              { printf("%s", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

/*4.3*/
%{
#include <stdio.h>

int char_count = 0;
int word_count = 0;
int line_count = 0;
%}

%%
\n              { line_count++; char_count++; printf("Newline detected\n"); }
[ \t]+          { char_count += yyleng; }
[a-zA-Z0-9]+    { word_count++; char_count += yyleng; }
.               { char_count++; }
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

    if(char_count>0)
    {
        line_count++;
    }
    
    printf("Characters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);

    return 0;
}

int yywrap() {
    return 1;
}





/*4.4*/
%{
#include <stdio.h>
#include <ctype.h>

int lower = 0, upper = 0, digit = 0, special = 0, length = 0;
%}

%%

[a-z]      { lower = 1; length++; }
[A-Z]      { upper = 1; length++; }
[0-9]      { digit = 1; length++; }
[*;#$@]    { special = 1; length++; }
.|\n       { length++; }

%%

int main() {
    yylex();
    if (length >= 9 && length <= 15 && lower && upper && digit && special) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }
    return 0;
}

int yywrap() {
    return 1;
}



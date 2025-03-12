#include <stdio.h>
#include <string.h>
#include <ctype.h>
// Function to validate the string against the regular expression a*bb int
validateString(const char *str) {
 int i = 0;

 // Check for zero or more 'a's
while (str[i] == 'a') { i++;
 }
 // Check if the next two characters are 'b' 
 if (str[i]
== 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
return 1; // Valid string
 }
 return 0; // Invalid string
}
int main() { char
input[100];
 // Prompt the user for input
 printf("Enter a string to validate: ");
if (fgets(input, sizeof(input), stdin) == NULL) {
printf("Error reading input.\n"); return 1;
 }
 // Remove the newline character if present
size_t len = strlen(input);
if (len > 0 && input[len - 1] == '\n') {
input[len - 1] = '\0';
 }

 // Validate the input string
if (validateString(input)) {
printf("Valid string\n");
 } else {
 printf("Invalid string\n");
 }
 return 0;
}
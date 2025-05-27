#include <stdio.h>
#include <stdlib.h>

/******* Function prototypes *******/
int countCharactersInString(const char *str);
void removeNewlineCharacter(char *str);
void concatenateStrings(char *dest, const char *src);
int areStringsEqual(const char *str1, const char *str2);

int main() {
    char testString[100] = "";
    printf("Enter a string: ");
    fgets(testString, sizeof(testString), stdin);
    
    // Remove the newline character if present
    removeNewlineCharacter(testString);

    // Count characters in the string
    int characterCount = countCharactersInString(testString);
    printf("The string '%s' contains %d character%s.\n", testString, characterCount, (characterCount == 1) ? "" : "s");
    
    // Input two strings for concatenation
    printf("You can concatenate two strings.\n");
    char firstString[50], secondString[50];
    printf("Enter the first string: ");
    fgets(firstString, sizeof(firstString), stdin);
    removeNewlineCharacter(firstString);
    printf("Enter the second string: ");
    fgets(secondString, sizeof(secondString), stdin);
    removeNewlineCharacter(secondString);
    char concatenatedString[100] = "";
    concatenateStrings(concatenatedString, firstString);
    concatenateStrings(concatenatedString, secondString);
    printf("Concatenated string: '%s'\n", concatenatedString);

    // Compare if two strings are equal
    printf("You can compare two strings.\n");
    char compareString1[50], compareString2[50];
    printf("Enter the first string to compare: ");
    fgets(compareString1, sizeof(compareString1), stdin);
    removeNewlineCharacter(compareString1);
    printf("Enter the second string to compare: ");
    fgets(compareString2, sizeof(compareString2), stdin);
    removeNewlineCharacter(compareString2);
    if (areStringsEqual(compareString1, compareString2)) {
        printf("The strings '%s' and '%s' are equal.\n", compareString1, compareString2);
    } else {
        printf("The strings '%s' and '%s' are not equal.\n", compareString1, compareString2);
    }
    
    return 0;
}


/******* Function definitions *******/
int countCharactersInString(const char *str) {
    int count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}

void removeNewlineCharacter(char *str) {
    char *p = str;
    while (*p != '\0') {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
        p++;
    }
}

void concatenateStrings(char *dest, const char *src) {
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Null-terminate the concatenated string
}

int areStringsEqual(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return 0; // Strings are not equal
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0'); // Both strings must end at the same time
}

#include <stdio.h>
#include <string.h>

void reverseString(char *str);

int main() {
    char str[100];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        reverseString(str);
        printf("Reversed string: %s\n", str);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}

// Reverses the given string in place
void reverseString(char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

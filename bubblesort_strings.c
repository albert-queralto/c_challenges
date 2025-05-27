#include <stdio.h>
#include <string.h>

#define MAX_STRINGS 5
#define MAX_LENGTH 100

void bubbleSort(char arr[][MAX_LENGTH], int n);

int main() {
    char arr[MAX_STRINGS][MAX_LENGTH] = {
        "banana",
        "apple",
        "orange",
        "grape",
        "cherry"
    };

    printf("Original array:\n");
    for (int i = 0; i < MAX_STRINGS; i++) {
        printf("%s\n", arr[i]);
    }

    bubbleSort(arr, MAX_STRINGS);

    printf("\nSorted array:\n");
    for (int i = 0; i < MAX_STRINGS; i++) {
        printf("%s\n", arr[i]);
    }

    return 0;
}

void bubbleSort(char arr[][MAX_LENGTH], int n) {
    char temp[MAX_LENGTH];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

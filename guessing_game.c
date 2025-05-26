#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()  {

    int random_number = 0;
    int guessedNumber = 0;
    int numberOfIterations = 5;

    srand((unsigned int)time(NULL)); // Seed the random number generator
    random_number = rand() % 21; // Generate a number between 0 and 20

    // Guess the number
    printf("Welcome to the Number Guessing Game!\n");
    for (int i = 0; i < numberOfIterations; i++) {
        printf("You have %d tr%s left.\n", numberOfIterations - i, (numberOfIterations - i) == 1 ? "y" : "ies");
        printf("Guess a number between 0 and 20: ");
        scanf("%d", &guessedNumber);
        if (guessedNumber < 0 || guessedNumber > 20) {
            printf("Please enter a number between 0 and 20.\n");
            i--; // Do not count this as a valid guess
        } else if (guessedNumber < random_number) {
            printf("Your guess is too low.\n");
        } else if (guessedNumber > random_number) {
            printf("Your guess is too high.\n");
        } else if (guessedNumber == random_number) {
            printf("Congratulations! You guessed the number: %d\n", random_number);
            return 0; // Exit the program if guessed correctly
        }
    }
    printf("Sorry, you've used all your guesses. The number was: %d\n", random_number);
    printf("Thank you for playing!\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()  {
    // Find all the prime numbers from 0 to 100
    int primes[100];
    int count = 0;
    for (int i = 2; i < 100; i++) {
        int is_prime = 1; // Assume i is prime
        // Check if i is divisible by any number from 2 to sqrt(i)
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = 0; // Found a divisor, not prime
                break;
            }
        }
        if (is_prime) {
            primes[count++] = i; // Store the prime number
        }
    }
    // Print the prime numbers
    printf("Prime numbers from 0 to 100:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", primes[i]);
    }
    printf("\n");
    
    return 0;
}

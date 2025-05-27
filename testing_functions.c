#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int greatestCommonDivisor(int a, int b);
float absoluteValue(float a);
float squareRoot(float a);


int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    int gcd = greatestCommonDivisor(a, b);
    printf("Greatest Common Divisor of %d and %d is: %d\n", a, b, gcd);

    float num;
    printf("Enter a number to find its square root: ");
    scanf("%f", &num);
    
    float sqrtResult = squareRoot(num);
    if (sqrtResult >= 0) {
        printf("Square root of %.2f is: %.2f\n", num, sqrtResult);
    }

    return 0;
}

// Function implementations
int greatestCommonDivisor(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

float absoluteValue(float a) {
    return (a < 0) ? -a : a;
}

float squareRoot(float a) {
    if (a < 0) {
        fprintf(stderr, "Error: Cannot compute square root of a negative number.\n");
        return -1.0; // Indicating an error
    }
    float x = a;
    float y = 1.0;
    float e = 0.000001; // precision
    while (absoluteValue(x - y) > e) {
        x = (x + y) / 2;
        y = a / x;
    }
    return x;
}

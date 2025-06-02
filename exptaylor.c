#include <stdio.h>
#include <stdlib.h>

double expTaylor(double arg);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    double arg = atof(argv[1]);
    double result = expTaylor(arg);
    printf("exp(%f) = %f\n", arg, result);
    
    return EXIT_SUCCESS;
}

double expTaylor (double arg) {
    const int K = 10;
    double x = arg;

    // Normalize x to be in the range [-0.5, 0.5]
    int m = 0;
    while (abs(x) > 0.5) {
        x /= 2.0;
        m++;
    }

    // Calculate the Taylor series expansion for exp(x) using Horner's algorithm
    double sum = 1.0;
    for (int n = K; n > 0; n--) {
        sum *= x / n;
        sum += 1.0;
    }

    for (int i = 0; i < m; i++) {
        sum *= sum;
    }
    return sum;
}

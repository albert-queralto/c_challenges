#include <stdio.h>
#include <stdlib.h>

double expPade(double arg);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    double arg = atof(argv[1]);
    double result = expPade(arg);
    printf("exp(%f) = %f\n", arg, result);
    
    return EXIT_SUCCESS;
}

double expPade(double arg) {
    const int K = 5;
    double x = arg;

    // Normalize x to be in the range [-0.5, 0.5]
    int m = 0;
    while (abs(x) > 0.5) {
        x /= 2.0;
        m++;
    }

    // Calculate the numerator and denominator of the Pade approximation
    double nom = 1.0;
    for (int n = K; n > 0; n--) {
        nom *= x * (K - n + 1) / (n * (2 * K - n + 1));
        nom += 1.0;
    }

    double denom = 1.0;
    for (int n = K; n > 0; n--) {
        denom *= -x * (K - n + 1) / (n * (2 * K - n + 1));
        denom += 1.0;
    }

    // Compute the final result
    double sum = nom / denom;
    for (int i = 0; i < m; i++) {
        sum *= sum;
    }
    return sum;

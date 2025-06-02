#include <stdio.h>
#include <math.h>

// Helper function to compute factorial
double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Taylor series for sin(x): sum of first N terms
double sinTaylor(int N, double x) {
    double sum = 0.0;
    for (int n = 0; n < N; n++) {
        double term = pow(-1, n) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
        sum += term;
    }
    return sum;
}

// Taylor series for cos(x): sum of first N terms
double cosTaylor(int N, double x) {
    double sum = 0.0;
    for (int n = 0; n < N; n++) {
        double term = pow(-1, n) * pow(x, 2 * n) / factorial(2 * n);
        sum += term;
    }
    return sum;
}

int main() {
    int N = 5;
    double x = 1.0; // Example value

    double sin_approx = sinTaylor(N, x);
    double cos_approx = cosTaylor(N, x);

    double sin_actual = sin(x);
    double cos_actual = cos(x);

    // (N+1)th term for error bound
    double sin_next_term = pow(-1, N) * pow(x, 2 * N + 1) / factorial(2 * N + 1);
    double cos_next_term = pow(-1, N) * pow(x, 2 * N) / factorial(2 * N);

    printf("sinTaylor(%d, %.2f) = %.10f\n", N, x, sin_approx);
    printf("sin(%.2f) = %.10f\n", x, sin_actual);
    printf("Error = %.10f\n", fabs(sin_actual - sin_approx));
    printf("Error bound (next term) = %.10f\n\n", fabs(sin_next_term));

    printf("cosTaylor(%d, %.2f) = %.10f\n", N, x, cos_approx);
    printf("cos(%.2f) = %.10f\n", x, cos_actual);
    printf("Error = %.10f\n", fabs(cos_actual - cos_approx));
    printf("Error bound (next term) = %.10f\n", fabs(cos_next_term));

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function f(x) = exp(x)
double f(double x) {
    return exp(x);
}

// Monte Carlo integration for dy/dx = f(x), x in [0,1]
double monte_carlo_integral(int samples) {
    double sum = 0.0;
    for (int i = 0; i < samples; i++) {
        double x = (double)rand() / RAND_MAX; // Random x in [0,1]
        sum += f(x);
    }
    return sum / samples; // Average value over [0,1]
}

int main() {
    srand(time(NULL));
    int N = 1000000; // Number of samples

    double result = monte_carlo_integral(N);
    printf("Monte Carlo estimate of y(1) = ∫₀¹ exp(x) dx: %f\n", result);
    printf("Analytical solution: %f\n", exp(1) - 1); // Analytical solution of ∫₀¹ exp(x) dx

    return 0;
}

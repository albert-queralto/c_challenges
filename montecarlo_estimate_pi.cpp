#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main() {
    const int numTrials = 10000000;

    std::srand(std::time(nullptr));

    int pointsInsideCircle = 0;

    for (int i = 0; i < numTrials; ++i) {
        double x = static_cast<double>(std::rand()) / RAND_MAX;
        double y = static_cast<double>(std::rand()) / RAND_MAX;

        if (std::sqrt(x * x + y * y) <= 1.0) {
            pointsInsideCircle++;
        }
    }

    double piEstimate = 4.0 * pointsInsideCircle / numTrials;
    std::cout << "Estimated value of Pi: " << piEstimate << std::endl;

    return 0;
}

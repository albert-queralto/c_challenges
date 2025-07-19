#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

struct Roots {
    bool real;
    double root1;
    double root2;
};

Roots solveQuadratic(double a, double b, double c) {
    Roots result;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        result.real = false;
        return result;
    }
    result.real = true;
    result.root1 = (-b + std::sqrt(discriminant)) / (2 * a);
    result.root2 = (-b - std::sqrt(discriminant)) / (2 * a);
    return result;
}


int main() {
    double a, b, c;
    std::cout << "Enter coefficients a, b, and c: ";
    std::cin >> a >> b >> c;

    Roots roots = solveQuadratic(a, b, c);
    if (!roots.real) {
        std::cout << "No real roots exist." << std::endl;
    } else if (roots.root1 == roots.root2) {
        std::cout << "One real root exists: " 
                    << std::fixed << std::setprecision(2) << roots.root1 << std::endl;
    } else {
        std::cout << "Two real roots exist: "
                    << std::fixed << std::setprecision(2) << roots.root1 << " and "
                    << std::fixed << std::setprecision(2) << roots.root2 << std::endl;
    }

    return 0;
}

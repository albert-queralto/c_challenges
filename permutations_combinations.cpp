
#include <iostream>


int factorial(int n) {
    if (n < 0) std::cerr << "Factorial of a negative number is undefined" << std::endl;
    if (n == 0 || n == 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

int permutations(int m, int n) {
    // nPr = m! / (m - n)!
    return factorial(m) / factorial(m - n);
}

int combinations(int m, int n) {
    // nCr = m! / (n! * (m - n)!)
    return factorial(m) / (factorial(n) * factorial(m - n));
}

int main() {
    std::cout << "Insert two numbers separated by space: " << std::endl;
    int m, n;
    std::cin >> m >> n;

    if (m < 0 || n < 0) {
        std::cerr << "Error: Both numbers must be non-negative." << std::endl;
        return 1;
    }
    if (m < n) {
        std::cerr << "Error: The first number must be greater than or equal to the second number." << std::endl;
        return 1;
    }
    
    std::string permutations_or_combinations;
    std::cout << "Do you want permutations or combinations? (p/c): ";
    std::cin >> permutations_or_combinations;

    if (permutations_or_combinations != "p" && permutations_or_combinations != "c") {
        std::cerr << "Error: Please enter 'p' for permutations or 'c' for combinations." << std::endl;
        return 1;
    }

    int result = 0;
    if (permutations_or_combinations == "p") {
        result = permutations(m, n);
    } else if (permutations_or_combinations == "c") {
        result = combinations(m, n);
    }

    std::cout << "The result is: " << result << std::endl;
    return 0;
}

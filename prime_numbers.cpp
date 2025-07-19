#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>


bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

std::vector<int> generatePrimes(int limit) {
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main() {
    int limit;
    std::cout << "Enter the upper limit to generate prime numbers: ";
    std::cin >> limit;

    std::vector<int> primes = generatePrimes(limit);
    std::cout << "Prime numbers up to " << limit << " are: ";
    for (int p : primes) {
        std::cout << p << " ";
    }
    return 0;
}

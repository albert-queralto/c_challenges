#include <iostream>
#include <vector>
#include <climits>

class Fibonacci {
public:
    // Function to generate Fibonacci sequence up to n terms
    std::vector<int> generate(int n) {
        std::vector<int> fib_sequence;
        if (n <= 0) return fib_sequence; // Return empty for non-positive n
        fib_sequence.push_back(0); // First Fibonacci number
        if (n == 1) return fib_sequence; // Return sequence with only the first number
        fib_sequence.push_back(1); // Second Fibonacci number
        for (int i = 2; i < n; ++i) {
            fib_sequence.push_back(fib_sequence[i - 1] + fib_sequence[i - 2]);
        }
        return fib_sequence;
    }

    // Function to find the largest Fibonacci number that fits in an int
    int largestFibonacci() {
        int a = 0, b = 1;
        while (b <= INT_MAX - a) { // Ensure we do not overflow
            int next = a + b;
            a = b;
            b = next;
        }
        return a; // Return the largest Fibonacci number that fits in an int
    }
};

int main() {
    Fibonacci fib;
    int n;
    std::cout << "Enter the number of terms: ";
    std::cin >> n;
    std::vector<int> sequence = fib.generate(n);
    std::cout << "Fibonacci sequence: ";
    for (int num : sequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    int largest = fib.largestFibonacci();
    std::cout << "Largest Fibonacci number that fits in an int: " << largest << " (up to " << INT_MAX << ")" << std::endl;
    return 0;
}

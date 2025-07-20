#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

class InputHandler {
public:
    int getNumberOfValues() {
        int N;
        std::cout << "Please enter the number of values you want to sum: ";
        std::cin >> N;
        std::cin.ignore(); // Clear the newline character from the input buffer
        return N;
    }

    std::vector<int> getValues() {
        std::vector<int> values;
        std::string input;
        std::cout << "Please enter some integers (press '|' to stop):" << std::endl;
        while (std::getline(std::cin, input)) {
            std::istringstream iss(input);
            std::string token;
            while (iss >> token) {
                if (token.find('|') != std::string::npos) {
                    // Handle numbers before '|'
                    size_t pos = token.find('|');
                    if (pos > 0) {
                        std::string num_part = token.substr(0, pos);
                        std::istringstream numstream(num_part);
                        int number;
                        if (num_part != "" && numstream >> number) {
                            values.push_back(number);
                        } else if (num_part != "") {
                            std::cout << "Invalid input. Please enter numeric values." << std::endl;
                            values.clear();
                            return values;
                        }
                    }
                    return values;
                }
                std::istringstream numstream(token);
                int number;
                if (numstream >> number) {
                    values.push_back(number);
                } else {
                    std::cout << "Invalid input. Please enter numeric values." << std::endl;
                    values.clear();
                    return values;
                }
            }
        }
        return values;
    }
};

class SumCalculator {
public:
    static bool canSumBeRepresentedAsInt(const std::vector<int>& values, int N, int& sum) {
        long long tempSum = 0;
        for (int i = 0; i < N; ++i) {
            tempSum += values[i];
            if (tempSum > std::numeric_limits<int>::max() || tempSum < std::numeric_limits<int>::min()) {
                return false;
            }
        }
        sum = static_cast<int>(tempSum);
        return true;
    }
};

class OutputHandler {
public:
    void printSum(const std::vector<int>& values, int N, int sum) {
        std::cout << "The sum of the first " << N << " numbers (";
        for (int i = 0; i < N; ++i) {
            std::cout << (i > 0 ? " " : "") << values[i];
        }
        std::cout << ") is " << sum << "." << std::endl;
    }
    void printError(const std::string& message) {
        std::cout << "Error: " << message << std::endl;
    }
};

int main() {
    InputHandler inputHandler;
    OutputHandler outputHandler;

    int N = inputHandler.getNumberOfValues();
    std::vector<int> values = inputHandler.getValues();

    if (values.empty()) {
        outputHandler.printError("Invalid input encountered.");
        return 1;
    }

    if (N > static_cast<int>(values.size())) {
        outputHandler.printError("Not enough values provided.");
        return 1;
    }

    int sum = 0;
    if (!SumCalculator::canSumBeRepresentedAsInt(values, N, sum)) {
        outputHandler.printError("The sum cannot be represented as an int.");
        return 1;
    }

    outputHandler.printSum(values, N, sum);
    return 0;
}

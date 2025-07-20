#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    int N;
    std::cout << "Please enter the number of values you want to sum: ";
    std::cin >> N;
    std::cin.ignore(); // Clear the newline character from the input buffer

    std::vector<int> values;
    std::string input;
    std::cout << "Please enter some integers (press '|' to stop):" << std::endl;
    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        std::string token;
        while (iss >> token) {
            if (token.find('|') != std::string::npos) {
                // If '|' is found, stop reading further tokens
                break;
            }
            std::istringstream numstream(token);
            int number;
            if (numstream >> number) {
                values.push_back(number);
            } else {
                std::cout << "Invalid input. Please enter numeric values." << std::endl;
                return 1;
            }
        }
        if (input.find('|') != std::string::npos) break;
    }

    if (N > values.size()) {
        std::cout << "Error: Not enough values provided." << std::endl;
        return 1;
    }

    int sum = 0;
    std::cout << "The sum of the first " << N << " numbers (";
    for (int i = 0; i < N; ++i) {
        sum += values[i];
        std::cout << (i > 0 ? " " : "") << values[i];
    }
    std::cout << ") is " << sum << "." << std::endl;
    return 0;
}

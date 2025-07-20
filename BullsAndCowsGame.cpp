#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>


class SecretNumberGenerator {
    public:
        static std::vector<int> generate(int length = 4) {
            std::vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(digits.begin(), digits.end(), g);
            return std::vector<int>(digits.begin(), digits.begin() + length);
        }
};


class InputHandler {
    public:
        static std::string getGuess() {
            std::string guess;
            std::cout << "Enter your guess (4 unique digits): ";
            std::cin >> guess;
            return guess;
        }

        static bool isValidGuess(const std::string& guess) {
            if (guess.length() != 4 || !std::all_of(guess.begin(), guess.end(), ::isdigit)) {
                return false;
            }
            std::vector<char> chars(guess.begin(), guess.end());
            return std::unique(chars.begin(), chars.end()) == chars.end();
        }

        static std::vector<int> toDigits(const std::string& guess) {
            std::vector<int> digits;
            for (char c : guess) {
                digits.push_back(c - '0');
            }
            return digits;
        }
};


class BullsAndCowsGame {
    private:
        std::vector<int> secretNumber;

    public:
        BullsAndCowsGame(const std::vector<int>& secret) : secretNumber(secret) {}

        void play() {
            int attempts = 0;
            while (true) {
                std::string guess = InputHandler::getGuess();
                if (!InputHandler::isValidGuess(guess)) {
                    std::cout << "Invalid input. Please enter exactly 4 unique digits." << std::endl;
                    continue;
                }
                std::vector<int> guessDigits = InputHandler::toDigits(guess);
                attempts++;

                int bulls = 0, cows = 0;
                for (int i = 0; i < 4; i++) {
                    if (guessDigits[i] == secretNumber[i]) {
                        bulls++;
                    } else if (std::find(secretNumber.begin(), secretNumber.end(), guessDigits[i]) != secretNumber.end()) {
                        cows++;
                    }
                }
                std::cout << "Attempt " << attempts << ": " << bulls << " Bulls, " << cows << " Cows" << std::endl;

                if (bulls == 4) {
                    std::cout << "Congratulations! You've guessed the secret number: ";
                    for (int digit : secretNumber) {
                        std::cout << digit;
                    }
                    std::cout << " in " << attempts << " attempts." << std::endl;
                    break;
                }
            }
        }
};


class GameApp {
    public:
        void run() {
            std::cout << "Welcome to the Bulls and Cows Game!" << std::endl;
            std::cout << "Try to guess the 4-digit secret number with unique digits." << std::endl;
            auto secret = SecretNumberGenerator::generate();
            BullsAndCowsGame game(secret);
            game.play();
        }
};


int main() {
    GameApp app;
    app.run();
    return 0;
}

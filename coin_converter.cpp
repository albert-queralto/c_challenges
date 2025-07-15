#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

int main() {
    int pennies, nickels, dimes, quarters, half_dollars, dollars;

    std::cout << "How many pennies do you have? ";
    std::cin >> pennies;
    std::cout << "How many nickels do you have? ";
    std::cin >> nickels;
    std::cout << "How many dimes do you have? ";
    std::cin >> dimes;
    std::cout << "How many quarters do you have? ";
    std::cin >> quarters;
    std::cout << "How many half dollars do you have? ";
    std::cin >> half_dollars;
    std::cout << "How many one-dollar coins do you have? ";
    std::cin >> dollars;

    int total_cents = pennies * 1 + nickels * 5 + dimes * 10 +
                      quarters * 25 + half_dollars * 50 + dollars * 100;

    auto print_coin = [](int count, const std::string& singular, const std::string& plural) {
        std::cout << "You have " << count << " " << (count == 1 ? singular : plural) << "." << std::endl;
    };

    print_coin(pennies, "penny", "pennies");
    print_coin(nickels, "nickel", "nickels");
    print_coin(dimes, "dime", "dimes");
    print_coin(quarters, "quarter", "quarters");
    print_coin(half_dollars, "half dollar", "half dollars");
    print_coin(dollars, "one-dollar coin", "one-dollar coins");

    std::cout << "The value of all of your coins is " << total_cents << " cents." << std::endl;
    std::cout << "That is $" << std::fixed << std::setprecision(2) << (total_cents / 100.0) << "." << std::endl;

    return 0;
}

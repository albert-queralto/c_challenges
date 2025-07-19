#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>



int main() {
    std::vector<double> temps;

    for (double temp; std::cin >> temp;) {
        temps.push_back(temp);
    }

    if (temps.empty()) {
        std::cout << "No temperatures provided." << std::endl;
        return 1;
    }

    double sum = 0;
    double high_temp = std::numeric_limits<double>::lowest();
    double low_temp = std::numeric_limits<double>::max();

    for (double x : temps) {
        if (x > high_temp) high_temp = x;
        if (x < low_temp) low_temp = x;
        sum += x;
    }

    double mean = sum / temps.size();

    std::cout << "High temperature: " << high_temp << std::endl;
    std::cout << "Low temperature: " << low_temp << std::endl;
    std::cout << "Mean temperature: " << mean << std::endl;

    return 0;
}

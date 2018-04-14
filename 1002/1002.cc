#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

int main(int argc, char **argv)
{
    std::cout << std::fixed << std::setprecision(1);

    std::map<int, float, std::greater<int>> polynomial;

    for (auto i = 0; i < 2; ++i) {
        int k;
        std::cin >> k;

        for (auto j = 0; j < k; ++j) {
            int exponent;
            float coefficient;
            std::cin >> exponent >> coefficient;

            if (polynomial.find(exponent) != polynomial.cend()) {
                polynomial[exponent] += coefficient;
            } else {
                polynomial[exponent] = coefficient;
            }
        }
    }
    
    for (const auto & p : polynomial) {
        if (std::abs(p.second) <= 1e-7f) {
            polynomial.erase(p.first);
        }
    }

    std::cout << polynomial.size();

    for (const auto & p : polynomial) {
        std::cout << " " << p.first << " " << p.second;
    }

    std::cout << std::endl;

    return 0;
}

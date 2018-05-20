#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

using Polynomia = std::map<int, float, std::greater<int>>;

void InputPolynomia(Polynomia &p)
{
    int k;
    std::cin >> k;

    for (int j = 0; j < k; ++j) {
        int exponent;
        float coefficient;
        std::cin >> exponent >> coefficient;

        p[exponent] = coefficient;
    }
}

void AddPolynomias(const Polynomia &pm1, const Polynomia &pm2, Polynomia &result)
{
    for (const auto &p1 : pm1) {
        for (const auto &p2 : pm2) {
            auto exponent = p1.first + p2.first;
            
            if (result.find(exponent) == result.cend()) {
                result[exponent] = 0;
            }

            result[exponent] += p1.second * p2.second;
        }
    }
}

int main(int argc, char *argv[])
{
    std::cout << std::fixed << std::setprecision(1);

    Polynomia p1, p2, result;

    InputPolynomia(p1);
    InputPolynomia(p2);
    AddPolynomias(p1, p2, result);

    for (const auto &p : result) {
        if (std::abs(p.second) <= 1e-7f) {
            result.erase(p.first);
        }
    }

    std::cout << result.size();

    for (const auto &p : result) {
        std::cout << " " << p.first << " " << p.second;
    }

    std::cout << std::endl;

    return 0;
}

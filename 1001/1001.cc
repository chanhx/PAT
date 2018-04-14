#include <iostream>

int main(int argc, char **argv)
{
    int a, b, sum;

    std::cin >> a >> b;
    sum = a + b;

    auto s = std::to_string(sum);
    auto len = s.length();

    for (auto i = 0; i < len; ++i) {
        std::cout << s[i];

        if (s[i] == '-') {continue;}

        auto bits_left = len - i - 1;
        if (bits_left != 0 && bits_left % 3 == 0)  {
            std::cout << ',';
        }
    }

    std::cout << std::endl;

    return 0;
}

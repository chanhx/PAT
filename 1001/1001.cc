#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
    int a, b;
    std::cin >> a >> b;

    auto s = std::to_string(a + b);
    auto len = s.length();

    std::ostringstream result;
    for (auto i = 0; i < len; ++i) {
        result << s[i];

        if (s[i] == '-') {continue;}

        auto bits_left = len - i - 1;
        if (bits_left != 0 && bits_left % 3 == 0)  {
            result << ',';
        }
    }

    std::cout << result.str() << std::endl;

    return 0;
}

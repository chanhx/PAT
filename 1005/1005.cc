#include <cstdio>
#include <cstring>

using namespace std;

const char * NUMBER[] = {
    "zero", "one", "two", "three", "four", 
    "five", "six", "seven", "eight", "nine"
};

char str[105];
int digits[6];

int main()
{
    scanf("%s", str);

    int sum = 0;
    for (int i = 0, len = strlen(str); i < len; ++i) {
        sum += str[i] - '0';
    }

    int i = 0;

    do {
        digits[i] = sum % 10;
        sum /= 10;
        ++i;
    } while (sum != 0);

    for (--i; i >= 0; --i) {
        printf("%s", NUMBER[digits[i]]);

        if (i != 0) {printf(" ");}
    }

    printf("\n");

    return 0;
}

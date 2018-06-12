#include <cstdio>
#include <cstring>

using namespace std;

char number[10000];

int main()
{
    char sign, ex_sign;
    int d1, exponent;

    scanf("%c%d.%sE", &sign, &d1, number+1);
    number[0] = d1 + '0';

    for (int i = 1, len = strlen(number); i < len; ++i) {
        if (number[i] == 'E') {
            sscanf(number+i+1, "%c%d", &ex_sign, &exponent);
            number[i] = '\0';
        }
    }

    if (sign == '-') {printf("-");}

    if (ex_sign == '+') {

        auto frac_len = strlen(number+1);

        if (exponent > frac_len) {
            int width = exponent - frac_len;
            printf("%s%0*d", number, width, 0);
        } else if (exponent == frac_len) {
            printf("%s", number);
        } else {
            printf("%.*s.%s", exponent + 1, number, number + exponent + 1);
        }
    } else {
        if (exponent == 0) {
            printf("%d.%s", d1, number + 1);
        } else {
            printf("0.%0*d%s", exponent, d1, number + 1);
        }
    }

    printf("\n");

    return 0;
}

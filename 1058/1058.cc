#include <cstdio>

int main()
{
    int a[3], b[3], c[3];

    scanf("%d.%d.%d", &a[0], &a[1], &a[2]);
    scanf("%d.%d.%d", &b[0], &b[1], &b[2]);

    for (auto i = 0; i < 3; ++i) {
        c[i] = a[i] + b[i];
    }

    c[1] += c[2] / 29;
    c[2] %= 29;

    c[0] += c[1] / 17;
    c[1] %= 17;

    printf("%d.%d.%d\n", c[0], c[1], c[2]);

    return 0;
}

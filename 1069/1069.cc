#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

const int kKaprekar = 6174;

inline void Int2Array(int n, int *a)
{
    for (int i = 0; i < 4; ++i) {
        a[i] = n % 10;
        n /= 10;
    }
}

inline void MaxMinFromArray(int *a, int &max, int &min)
{
    max = 0, min = 0;
    for (int i = 0; i < 4; ++i) {
        max *= 10;
        max += a[i];

        min *= 10;
        min += a[3-i];
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int num[4];

    for (int max = 0, min = 0, diff = n;;) {

        Int2Array(diff, num);
        sort(num, num + 4, greater<int>());
        
        MaxMinFromArray(num, max, min);

        diff = max - min;

        printf("%04d - %04d = %04d\n", max, min, diff);

        if (diff == 0 || diff == kKaprekar) {break;}
    }

    return 0;
}

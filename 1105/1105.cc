#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    int N;
    scanf("%d", &N);

    int m = ceil(sqrt(N));
    while (N % m != 0) {
        ++m;
    }
    int n = N / m;

    vector<int> seq(N);
    vector<vector<int>> matrix(m, vector<int>(n));

    for (auto &v : seq) {
        scanf("%d", &v);
    }
    sort(seq.begin(), seq.end());

    for (int i = N-1, x = 0, y = 0, u = 0, d = m, r = n, l = -1; 
         i >= 0;
         ++x, ++y, --r, ++l, --d, ++u)
    {
        for (; i >= 0 && x < r; ++x, --i) {
            matrix[y][x] = seq[i];
        }
        for (--x, ++y; i >= 0 && y < d; ++y, --i) {
            matrix[y][x] = seq[i];
        }
        for (--y, --x; i >= 0 && x > l; --x, --i) {
            matrix[y][x] = seq[i];
        }
        for (++x, --y; i >= 0 && y > u; --y, --i) {
            matrix[y][x] = seq[i];
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d%c", matrix[i][j], j == n-1 ? '\n' : ' ');
        }
    }

    return 0;
}
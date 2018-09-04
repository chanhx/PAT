#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Window
{
    queue<int> customers;
    int end_time;
    int front_time;
};

inline int ConvertTime(int h, int m)
{
    return h * 60 + m;
}

int main()
{
    int n, m, k, q;
    scanf("%d %d %d %d", &n, &m, &k, &q);

    int begin_time = ConvertTime(8, 0);
    int end_time = ConvertTime(17, 0);

    vector<int> done_time(k+1);
    vector<bool> sorry(k+1, false);
    vector<Window> windows(n+1, {queue<int>(), begin_time, begin_time});

    for (int i = 1, capacity_inside = m*n, t; i <= k; ++i) {
        scanf("%d", &t);

        int wi;
        if (i <= capacity_inside) {
            wi = (i - 1) % n + 1;
        } else {
            for (int j = 1, earliest = INF; j <= n; ++j) {
                auto &w = windows[j];
                if (w.front_time < earliest) {
                    earliest = w.front_time;
                    wi = j;
                }
            }
        }

        auto &w = windows[wi];

        if (w.end_time >= end_time) {
            sorry[i] = true;
        }

        w.customers.push(t);
        w.end_time += t;

        if (w.front_time == 0) {
            w.front_time = w.end_time;
        } else if (i > capacity_inside) {
            w.customers.pop();
            w.front_time += w.customers.front();
        }

        done_time[i] = w.end_time;
    }

    for (int i = 1; i <= q; ++i) {
        int c;
        scanf("%d", &c);

        auto dt = done_time[c];

        if (sorry[c]) {
            printf("Sorry\n");
        } else {
            printf("%02d:%02d\n", dt / 60, dt % 60);
        }
    }

    return 0;
}
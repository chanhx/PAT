#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Customer
{
    int arriving_time;
    int processing_time;
};

inline int ConvertTime(int h, int m, int s)
{
    return h * 3600 + m * 60 + s;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int begin_time = ConvertTime(8, 0, 0);
    int end_time = ConvertTime(17, 0, 0);

    vector<Customer> customers;
    vector<int> windows(k, begin_time);

    for (int i = 0; i < n; ++i) {
        int h, m, s, processing_time;
        scanf("%d:%d:%d %d", &h, &m, &s, &processing_time);
        int arriving_time = ConvertTime(h, m, s);

        if (arriving_time > end_time) {continue;}

        processing_time = processing_time > 60 ? 3600 : processing_time * 60;
        customers.push_back({arriving_time, processing_time});
    }

    sort(customers.begin(), customers.end(),
         [](Customer &c1, Customer &c2) {
             return c1.arriving_time < c2.arriving_time;
         });

    double waiting_time = 0;

    for (auto &c : customers) {
        int wi, earliest_end_time = INF;
        for (int i = 0; i < k; ++i) {
            if (windows[i] < earliest_end_time) {
                wi = i;
                earliest_end_time = windows[i];
            }
        }

        if (earliest_end_time <= c.arriving_time) {
            windows[wi] = c.arriving_time + c.processing_time;
        } else {
            waiting_time += earliest_end_time - c.arriving_time;
            windows[wi] += c.processing_time;
        }
    }

    printf("%.1f\n", waiting_time / 60 / customers.size());

    return 0;
}
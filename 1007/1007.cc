#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);

    vector<int> seq(n);
    for (auto &d : seq) {
        scanf("%d", &d);
    }

    vector<int> sum(n), start(n);
    sum[0] = seq[0];
    start[0] = 0;

    for (int i = 1, len = seq.size(); i < len; ++i) {
        int s = sum[i-1] + seq[i];
        if (s > seq[i]) {
            sum[i] = s;
            start[i] = start[i-1];
        } else {
            sum[i] = seq[i];
            start[i] = i;
        }
    }

    int max_sum_i = 0;
    for (int i = 1, len = sum.size(); i < len; ++i) {
        if (sum[i] > sum[max_sum_i]) {
            max_sum_i = i;
        }
    }

    if (sum[max_sum_i] < 0) {
        printf("0 %d %d\n", seq[0], seq[n-1]);
    } else {
        printf("%d %d %d\n", sum[max_sum_i], seq[start[max_sum_i]], seq[max_sum_i]);
    }

    return 0;
}

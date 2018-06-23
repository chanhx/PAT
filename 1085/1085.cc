#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, p;
    scanf("%d %d", &n, &p);

    vector<int> seq(n);

    for (auto &a : seq) {
        scanf("%d", &a);
    }

    sort(seq.begin(), seq.end());

    int len = 0;
    for (auto it = seq.cbegin(), end = seq.cend(); it != end; ++it) {
        auto it2 = upper_bound(it, end, (long long)*it * p);
        int d = distance(it, it2);
        len = d > len ? d : len;
    }
    
    printf("%d\n", len);

    return 0;
}

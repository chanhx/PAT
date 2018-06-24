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
    for (auto it1 = seq.cbegin(), it2 = seq.cbegin(), end = seq.cend(); 
         it2 != end && it1 != end;
         ++it1)
    {
        for (; it2 != end; ++it2) {
            if (*it2 > (long long)*it1 * p) {
                break;
            }
            int d = distance(it1, it2) + 1;
            len = d > len ? d : len;
        }
    }
    
    printf("%d\n", len);

    return 0;
}

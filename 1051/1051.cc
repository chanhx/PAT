#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);

    vector<int> seq(n);

    for (int i = 0; i < k; ++i) {

        stack<int> s;

        for (auto &num : seq) {
            scanf("%d", &num);
        }

        for (int num = 1, j = 0; j < n && num <= n + 1;) {

            if (num == seq[j] && s.size() < m) {
                ++j;
                ++num;
            } else if (s.size() > 0 && s.top() == seq[j]) {
                s.pop();
                ++j;
            } else if (num <= n && s.size() < m) {
                s.push(num);
                ++num;
            } else {
                break;
            }
        }

        if (s.size() == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}

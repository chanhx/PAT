#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    vector<int> coins(n, 0);
    for (auto &c : coins) {
        scanf("%d", &c);
    }
    sort(coins.begin(), coins.end(), greater<int>());

    vector<int> dp(m+1, 0);
    vector<vector<bool>> selected(n, vector<bool>(m+1, false));

    for (int i = 0; i < n; ++i) {
        for (int v = m; v >= coins[i]; --v) {
            if (dp[v-coins[i]] + coins[i] < dp[v]) {
                continue;
            }
            dp[v] = dp[v-coins[i]] + coins[i];
            selected[i][v] = true;
        }
    }

    if (dp[m] != m) {
        printf("No Solution\n");
        return 0;
    }

    for (int i = n-1, v = m; i >= 0; --i) {
        if (selected[i][v]) {
            v -= coins[i];
            printf("%d%c", coins[i], v == 0 ? '\n' : ' ');
        }
    }

    return 0;
}

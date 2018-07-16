#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool dfs(int i, int m, vector<int> &coins, vector<int> &left_sum, vector<int> &ans)
{
    if (m == 0) {
        return true;
    }

    if (m < 0 || i >= coins.size() || m > left_sum[i]) {
        return false;
    }

    if (dfs(i+1, m-coins[i], coins, left_sum, ans)) {
        ans.push_back(coins[i]);
        return true;
    } else if (dfs(i+1, m, coins, left_sum, ans)) {
        return true;
    }

    return false;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    vector<int> coins(n, 0), left_sum(n, 0);
    
    for (auto &c : coins) {
        scanf("%d", &c);
    }
    sort(coins.begin(), coins.end());

    for (int i = n-1, sum = 0; i >= 0; --i) {
        sum += coins[i];
        left_sum[i] = sum;
    }

    vector<int> ans;
    if (dfs(0, m, coins, left_sum, ans)) {
        for (int i = ans.size()-1; i >= 0; --i) {
            printf("%d%c", ans[i], i == 0 ? '\n' : ' ');
        }
    } else {
        printf("No Solution\n");
    }

    return 0;
}

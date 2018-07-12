#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n, m, l;
    scanf("%d %d", &n, &m);

    vector<int> fav_colors(m+1);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &fav_colors[i]);
    }

    scanf("%d", &l);
    vector<int> colors(l+1);
    for (int i = 1; i <= l; ++i) {
        scanf("%d", &colors[i]);
    }

    vector<vector<int>> dp(m+1, vector<int>(l+1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= l; ++j) {
            int max_l = max(dp[i-1][j], dp[i][j-1]);
            dp[i][j] = fav_colors[i] == colors[j] ? 
                        max_l + 1 : 
                        max_l;
        }
    }

    printf("%d\n", dp[m][l]);

    return 0;
}

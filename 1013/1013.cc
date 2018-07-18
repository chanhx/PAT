#include <cstdio>
#include <vector>

using namespace std;

void dfs(int city, vector<vector<int>> &graph, vector<bool> &visited)
{
    for (auto &c : graph[city]) {
        if (visited[c]) {
            continue;
        }
        visited[c] = true;
        dfs(c, graph, visited);
    }
}

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    vector<vector<int>> graph(n+1, vector<int>());
    vector<int> cities(k);

    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (auto &c : cities) {
        scanf("%d", &c);

        int block = 0;
        vector<bool> visited(n+1, false);
        visited[c] = true;

        for (int i = 1; i <= n; ++i) {
            if (i != c && !visited[i]) {
                dfs(i, graph, visited);
                ++block;
            }
        }
        
        printf("%d\n", block-1);
    }

    return 0;
}

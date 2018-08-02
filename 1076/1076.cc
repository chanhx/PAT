#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int MaxForwardsAmount(int v, vector<vector<int>> &graph, int level)
{
    int count = 0;

    vector<bool> visited(graph.size(), false);

    queue<int> q;
    q.push(v);
    visited[v] = true;

    for (int qsize = q.size(); qsize > 0 && level != 0; qsize = q.size(), level -= 1) {
        for (int j = 0; j < qsize; ++j) {
            int i = q.front();
            q.pop();

            for (const auto &vi : graph[i]) {
                if (visited[vi]) {continue;}

                ++count;
                visited[vi] = true;

                if (level <= 1) {continue;}
                q.push(vi);
            }
        }
    }

    return count;
}

int main()
{
    int n, l, k;
    scanf("%d %d", &n, &l);

    vector<vector<int>> graph(n+1, vector<int>());

    for (int i = 1; i <= n; ++i) {
        int follows_count;
        scanf("%d", &follows_count);
        for (int j = 0; j < follows_count; ++j) {
            int v;
            scanf("%d", &v);
            graph[v].push_back(i);
        }
    }

    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        int v;
        scanf("%d", &v);

        printf("%d\n", MaxForwardsAmount(v, graph, l));
    }

    return 0;
}

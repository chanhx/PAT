#include <cstdio>
#include <cstdlib>
#include <vector>
#include <limits>

using namespace std;

const auto INF = numeric_limits<int>::max();

void Dijkstra(vector<vector<int>> &graph,
              vector<vector<int>> &pre)
{
    int size = graph.size();
    auto dist = graph[0];
    vector<bool> visited(size, false);

    dist[0] = 0;

    for (int i = 0; i < size; ++i) {
        int u = -1, min = INF;
        for (int j = 0; j < size; ++j) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) {
            return;
        }

        visited[u] = true;

        for (int i = 0; i < size; ++i) {
            if (visited[i] || graph[u][i] == INF) {
                continue;
            }

            auto new_dist_i = dist[u] + graph[u][i];

            if (new_dist_i < dist[i]) {
                dist[i] = new_dist_i;
                pre[i].clear();
                pre[i].push_back(u);
            } else if (new_dist_i == dist[i]) {
                pre[i].push_back(u);
            }
        }
    }
}

void DFS(vector<vector<int>> &routes, 
         vector<int> &best_route,
         vector<int> &weight,
         vector<int> &route,
         int v,
         int &min_need,
         int &min_remain,
         int need,
         int remain)
{
    if (v == 0) {
        need = abs(need);
        if (need < min_need || remain < min_remain) {
            min_need = need;
            min_remain = remain;
            best_route = route;
        }

        return;
    }

    route.push_back(v);

    need += weight[v];
    if (need > 0) {
        remain += need;
        need = 0;
    }

    for (const auto &pv : routes[v]) {
        DFS(routes, best_route, weight, route, pv, min_need, min_remain, need, remain);
    }

    route.pop_back();
}

int main()
{
    int c_max, n, index, m;
    scanf("%d %d %d %d", &c_max, &n, &index, &m);

    vector<vector<int>> graph(n+1, vector<int>(n+1, INF));
    vector<int> bikes(n+1);

    for (int i = 1, c_perfect = c_max/2; i <= n; ++i) {
        int b;
        scanf("%d", &b);
        bikes[i] = b - c_perfect;
    }

    for (int i = 0; i < m; ++i) {
        int s1, s2, d;
        scanf("%d %d %d", &s1, &s2, &d);
        graph[s1][s2] = d;
        graph[s2][s1] = d;
    }

    vector<vector<int>> routes(n+1, vector<int>());
    vector<int> route, temp_route;
    int min_need = INF, min_remain = INF;

    Dijkstra(graph, routes);
    DFS(routes, route, bikes, temp_route, index, min_need, min_remain, 0, 0);

    printf("%d 0", min_need);

    for (auto it = route.crbegin(), end = route.crend(); it != end; ++it) {
        printf("->%d", *it);
    }

    printf(" %d\n", min_remain);

    return 0;
}
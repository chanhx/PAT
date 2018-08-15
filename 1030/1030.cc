#include <cstdio>
#include <vector>
#include <limits>
#include <stack>

using namespace std;

const auto INF = numeric_limits<int>::max();

void Dijkstra(vector<vector<int>> &graph,
              vector<vector<int>> &cost,
              vector<int> &pre,
              int s,
              int d,
              int &total_dist,
              int &total_cost)
{
    int size = graph.size();
    vector<bool> visited(size, false);

    auto dist = graph[s];
    auto cost_s = cost[s];

    for (int i = 0; i < size; ++i) {
        pre[i] = s;
    }

    dist[s] = 0;
    cost_s[s] = 0;

    for (int i = 0; i < size; ++i) {
        int u = -1, min = INF;
        for (int j = 0; j < size; ++j) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = true;

        for (int i = 0; i < size; ++i) {
            if (visited[i] || graph[u][i] == INF) {
                continue;
            }

            auto new_dist_i = dist[u] + graph[u][i];
            auto new_cost_i = cost_s[u] + cost[u][i];

            if (new_dist_i < dist[i]) {
                dist[i] = new_dist_i;
                cost_s[i] = new_cost_i;
                pre[i] = u;
            } else if (new_dist_i == dist[i] && 
                       new_cost_i < cost_s[i])
            {
                cost_s[i] = new_cost_i;
                pre[i] = u;
            }

            if (i == d) {
                total_dist = dist[i];
                total_cost = cost_s[i];
            }
        }
    }
}

void PrintRoute(vector<int> &pre, int s, int d)
{
    stack<int> stk;

    for (int v = d, pre_v = pre[d];;) {
        stk.push(v);

        if (v == s) {break;}

        v = pre_v;
        pre_v = pre[v];
    }

    while (!stk.empty()) {
        printf("%d ", stk.top());
        stk.pop();
    }
}

int main()
{
    int m, n, s, d;
    scanf("%d %d %d %d", &m, &n, &s, &d);

    vector<vector<int>> 
        graph(m, vector<int>(m, INF)), 
        cost(m, vector<int>(m, INF));

    for (int i = 0; i < n; ++i) {
        int c1, c2, dist, _cost;
        scanf("%d %d %d %d", &c1, &c2, &dist, &_cost);

        graph[c1][c2] = dist;
        graph[c2][c1] = dist;

        cost[c1][c2] = _cost;
        cost[c2][c1] = _cost;
    }

    vector<int> pre(m);
    int total_dist, total_cost;

    Dijkstra(graph, cost, pre, s, d, total_dist, total_cost);

    PrintRoute(pre, s, d);

    printf("%d %d\n", total_dist, total_cost);

    return 0;
}
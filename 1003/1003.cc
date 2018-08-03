#include <cstdio>
#include <vector>
#include <limits>

using namespace std;

const auto INF = numeric_limits<int>::max();

void Dijkstra(int s, vector<vector<int>> &graph, vector<int> &weights, 
              vector<int> &count, vector<int> &route_weights)
{
    int size = weights.size();

    vector<bool> visited(size, false);
    auto dist = graph[s];

    dist[s] = 0;
    count[s] = 1;
    route_weights[s] = weights[s];

    for (int i = 0; i < size; ++i) {
        int u = -1, min = INF;
        for (int j = 0; j < size; ++j) {
            if (!visited[j] && dist[j] < min) {
                u = j;
                min = dist[j];
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
            auto new_route_weight_i = route_weights[u] + weights[i];

            if (new_dist_i < dist[i]) {
                dist[i] = new_dist_i;
                route_weights[i] = new_route_weight_i;
                count[i] = count[u];
            } else if (new_dist_i == dist[i]) {
                if (new_route_weight_i > route_weights[i]) {
                    route_weights[i] = new_route_weight_i;
                }
                count[i] += count[u];
            }
        }
    }
}

int main()
{
    int n, m, c1, c2;
    scanf("%d %d %d %d", &n, &m, &c1, &c2);

    vector<vector<int>> graph(n, vector<int>(n, INF));
    vector<int> teams(n), total_teams(n, 0), routes(n, 0);

    for (auto &t : teams) {
        scanf("%d", &t);
    }

    for (int i = 0; i < m; ++i) {
        int c1, c2, l;
        scanf("%d %d %d", &c1, &c2, &l);
        graph[c1][c2] = l;
        graph[c2][c1] = l;
    }

    Dijkstra(c1, graph, teams, routes, total_teams);

    printf("%d %d\n", routes[c2], total_teams[c2]);

    return 0;
}

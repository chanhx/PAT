#include <cstdio>
#include <cstdlib>
#include <vector>
#include <limits>

using namespace std;

const auto INF = numeric_limits<int>::max();

void Dijkstra(vector<vector<int>> &graph, 
             int v,
             int n,
             int m,
             int d,
             float &average_dist,
             float &min_dist)
{
    int size = n + m;
    auto dist = graph[v];
    vector<bool> visited(n, false);

    dist[v] = 0;
    bool found_min = false;

    for (int i = 0; i < size; ++i) {
        int u = -1, min = INF;
        for (int j = 1; j <= size; ++j) {
            if (!visited[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }

        if (u == -1) {
            return;
        }

        visited[u] = true;

        if (!found_min && u <= n) {
            min_dist = min;
            found_min = true;
        }

        if (u <= n && dist[u] > d) {
            min_dist = -1;
            return;
        }

        for (int i = 1; i <= size; ++i) {
            if (visited[i] || graph[u][i] == INF) {
                continue;
            }

            auto new_dist_i = dist[u] + graph[u][i];
            if (new_dist_i < dist[i]) {
                dist[i] = new_dist_i;
            }
        }
    }

    average_dist = 0;
    for (int i = 1; i <= n; ++i) {
        average_dist += dist[i];
    }
    average_dist /= n;
}

inline int Str2Index(const int n, char v[])
{
    return v[0] == 'G' ? atoi(v+1) + n : atoi(v);
}

int main()
{
    int n, m, k, d;
    scanf("%d %d %d %d", &n, &m, &k, &d);

    vector<vector<int>> graph(n+m+1, vector<int>(n+m+1, INF));

    char v[6];
    for (int i = 0; i < k; ++i) {
        int v1, v2, dist;

        scanf("%s", v);
        v1 = Str2Index(n, v);
        scanf("%s %d", v, &dist);
        v2 = Str2Index(n, v);

        graph[v1][v2] = dist;
        graph[v2][v1] = dist;
    }

    vector<int> dist(m+1);
    int index = -1;
    float min_dist = -1, average_dist = INF;

    for (int i = 1; i <= m; ++i) {
        float v_min_dist, v_average_dist;
        Dijkstra(graph, n+i, n, m, d, v_average_dist, v_min_dist);

        if (v_min_dist == -1) {continue;}

        if (v_min_dist > min_dist) {
            average_dist = v_average_dist;
            min_dist = v_min_dist;
            index = i;
        } else if (v_min_dist == min_dist && v_average_dist < average_dist) {
            average_dist = v_average_dist;
            index = i;
        }
    }

    if (index == -1) {
        printf("No Solution\n");
    } else {
        printf("G%d\n", index);
        printf("%.1f %.1f\n", min_dist, average_dist);
    }

    return 0;
}
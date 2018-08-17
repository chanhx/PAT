#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include <stack>

using namespace std;

const auto INF = numeric_limits<int>::max();
const string ROM = "ROM";

void Dijkstra(vector<vector<int>> &graph,
              vector<int> &weights,
              vector<int> &pre,
              int s,
              int t,
              int &routes_count,
              int &t_dist,
              int &weight,
              int &average_weight)
{
    int size = graph.size();
    auto dist = graph[s];
    vector<bool> visited(size, false);

    vector<int> route_weights(size, 0);
    vector<int> cities_counts(size, 0);
    vector<int> routes_counts(size, 0);

    dist[s] = 0;
    pre[s] = s;
    routes_counts[s] = 1;

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

            auto new_dist = dist[u] + graph[u][i];
            auto new_route_weight = route_weights[u] + weights[i];

            if (new_dist < dist[i]) {
                dist[i] = new_dist;
                route_weights[i] = new_route_weight;
                cities_counts[i] = cities_counts[u] + 1;
                pre[i] = u;
                routes_counts[i] = routes_counts[u];
            } else if (new_dist == dist[i]) {
                routes_counts[i] += routes_counts[u];

                if (new_route_weight > route_weights[i]) {
                    cities_counts[i] = cities_counts[u] + 1;
                    route_weights[i] = new_route_weight;
                    pre[i] = u;
                } else if (new_route_weight == route_weights[i] &&
                           cities_counts[u] + 1 < cities_counts[i])
                {
                    cities_counts[i] = cities_counts[u] + 1;
                    pre[i] = u;
                }
            }
        }
    }

    routes_count = routes_counts[t];
    t_dist = dist[t];
    weight = route_weights[t];
    average_weight = route_weights[t] / cities_counts[t];
}

void PrintRoute(vector<int> &pre, map<int, string> cities, int s, int t)
{
    stack<int> stk;
    stk.push(t);

    for (int v = stk.top(), pre_v = pre[v];;) {
        stk.push(pre_v);

        if (pre_v == s) {break;}

        v = pre_v;
        pre_v = pre[v];
    }

    while (!stk.empty()) {
        auto c = stk.top();
        cout << cities[c];

        if (c != t) {
            cout << "->";
        }
        stk.pop();
    }
    cout << endl;
}

int main()
{
    int n, k;
    string s;
    cin >> n >> k >> s;

    vector<vector<int>> graph(n, vector<int>(n, INF));
    vector<int> happiness(n, 0);
    map<string, int> city_ids;
    map<int, string> cities;

    cities[0] = s;
    city_ids[s] = 0;

    for (int i = 1; i < n; ++i) {
        string city;
        cin >> city >> happiness[i];

        cities[i] = city;
        city_ids[city] = i;
    }

    for (int i = 0; i < k; ++i) {
        string c1, c2;
        int cost;
        cin >> c1 >> c2 >> cost;

        const int id1 = city_ids[c1], id2 = city_ids[c2];
        graph[id1][id2] = cost;
        graph[id2][id1] = cost;
    }

    vector<int> pre(n);
    int routes_count, cost, total_happiness, average_happiness;

    Dijkstra(graph, happiness, pre, 0, city_ids[ROM], 
             routes_count, cost, total_happiness, average_happiness);

    printf("%d %d %d %d\n", routes_count, cost, total_happiness, average_happiness);
    PrintRoute(pre, cities, city_ids[s], city_ids[ROM]);

    return 0;
}
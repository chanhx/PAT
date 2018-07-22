#include <cstdio>
#include <vector>
#include <queue>
#include <set>

using namespace std;

void BFS(int a, vector<vector<int>> &graph, set<int> &roots, vector<bool> &visited)
{
    queue<int> q;
    q.push(a);

    for (int qsize = q.size(), vertex_left = graph.size() - 1; 
         qsize > 0; 
         qsize = q.size())
    {
        bool meet_farthest_roots = vertex_left == qsize;

        for (int i = 0; i < qsize; ++i) {
            auto v = q.front();
            q.pop();

            visited[v] = true;
            --vertex_left;

            if (meet_farthest_roots) {
                roots.insert(v);
                continue;
            }

            for (const auto &vi : graph[v]) {
                if (visited[vi]) {continue;}
                q.push(vi);
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<vector<int>> graph(n+1, vector<int>());

    for (int i = 1; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<bool> visited(n+1, false);
    set<int> roots;
    int components = 0;

    for (int i = 1; i <= n; ++i) {
        if (visited[i]) {continue;}
        ++components;
        BFS(i, graph, roots, visited);
    }

    if (components > 1) {
        printf("Error: %d components\n", components);
        return 0;
    }

    visited = decltype(visited)(n+1, false);
    BFS(*roots.cbegin(), graph, roots, visited);

    for (const auto &r : roots) {
        printf("%d\n", r);
    }

    return 0;
}

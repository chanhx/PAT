#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Gang
{
    string head;
    int total_weight = 0;
    vector<int> members;
};

int IDForName(string name,
              unordered_map<string, int> &ids,
              vector<string> &names)
{
    if (ids.find(name) != ids.cend()) {
        return ids[name];
    }

    int id = ids.size();
    ids[name] = id;
    names.push_back(name);

    return id;
}

void BFS(int i, vector<unordered_set<int>> &graph, vector<bool> &visited, 
         unordered_map<int, int> &weights, Gang &gang)
{
    queue<int> q;
    q.push(i);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (visited[v]) {continue;}

        gang.members.push_back(v);
        gang.total_weight += weights[v];

        visited[v] = true;

        for (auto vi : graph[v]) {
            if (visited[vi]) {continue;}
            q.push(vi);
        }
    }

    gang.total_weight /= 2;
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<unordered_set<int>> graph;
    unordered_map<string, int> ids;
    vector<string> names;
    unordered_map<int, int> weights;

    for (int i = 0; i < n; ++i) {
        string a, b;
        int t;
        cin >> a >> b >> t;

        int id_a = IDForName(a, ids, names), id_b = IDForName(b, ids, names);

        if (weights.find(id_a) == weights.cend()) {
            weights[id_a] = 0;
            graph.push_back(unordered_set<int>());
        }
        if (weights.find(id_b) == weights.cend()) {
            weights[id_b] = 0;
            graph.push_back(unordered_set<int>());
        }

        weights[id_a] += t;
        weights[id_b] += t;

        graph[id_a].insert(id_b);
        graph[id_b].insert(id_a);
    }

    vector<bool> visited(ids.size(), false);
    vector<Gang> gangs;

    for (const auto &p : ids) {
        if (visited[p.second]) {
            continue;
        }

        Gang gang;
        BFS(p.second, graph, visited, weights, gang);

        if (gang.members.size() > 2 && gang.total_weight > k) {
            gangs.push_back(gang);
        }
    }

    cout << gangs.size() << endl;

    for (auto &g : gangs) {
        auto max_it = max_element(g.members.cbegin(), g.members.cend(),
                                  [&weights](int a, int b) {
                                      return weights[a] < weights[b];
                                  });
        g.head = names[*max_it];
    }

    sort(gangs.begin(), gangs.end(), [](const Gang &ga, const Gang &gb) {
        return ga.head < gb.head;
    });

    for (const auto &g : gangs) {
        cout << g.head << ' ' << g.members.size() << endl;
    }

    return 0;
}

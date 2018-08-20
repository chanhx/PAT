#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

void DFS(const vector<vector<int>> &tree,
         const vector<int> &weight,
         vector<int> &leaves,
         const int s,
         int id,
         int current_s)
{
    current_s += weight[id];

    if (current_s == s && tree[id].empty()) {
        leaves.push_back(id);
        return;
    }

    for (const auto &sid : tree[id]) {
        auto new_s = weight[sid] + current_s;

        if (tree[sid].empty()) {
            if (new_s == s) {
                leaves.push_back(sid);
            }
            continue;
        }

        if (new_s >= s) {
            continue;
        }

        DFS(tree, weight, leaves, s, sid, current_s);
    }
}

void PrintPath(const vector<int> &parent, 
               const vector<int> &weight,
               const int leaf)
{
    stack<int> s;

    for (int i = leaf; i != -1; i = parent[i]) {
        s.push(i);
    }

    for (bool empty = s.empty(); !empty; ) {
        auto id = s.top();
        s.pop();
        empty = s.empty();

        printf("%d%c", weight[id], empty ? '\n' : ' ');
    }
}

int main()
{
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    vector<vector<int>> tree(n);
    vector<int> weight(n);
    vector<int> direct_parent(n, -1);

    for (auto &w : weight) {
        scanf("%d", &w);
    }

    for (int i = 0; i < m; ++i) {
        int id, k;
        scanf("%d %d", &id, &k);

        auto &tree_id = tree[id];
        tree_id = vector<int>(k);

        for (auto &sid : tree_id) {
            scanf("%d", &sid);
            direct_parent[sid] = id;
        }

        sort(tree_id.begin(), tree_id.end(), 
            [&weight](int a, int b) {
                return weight[a] > weight[b];
            });
    }

    vector<int> leaves;
    DFS(tree, weight, leaves, s, 0, 0);

    for (auto id : leaves) {
        PrintPath(direct_parent, weight, id);
    }

    return 0;
}
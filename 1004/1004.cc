#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void BFS(const vector<vector<int>> &tree)
{
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int count = 0;

        for (int i = 0, size = q.size(); i < size; ++i) {
            int id = q.front();
            q.pop();

            if (tree[id].empty()) {
                ++count;
                continue;
            }

            for (auto it = tree[id].cbegin()+1, end = tree[id].cend();
                 it != end;
                 ++it)
            {
                q.push(*it);
            }
        }

        printf("%d%c", count, q.empty() ? '\n' : ' ');
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    vector<vector<int>> tree(n+1);

    for (int i = 0; i < m; ++i) {
        int id, k;
        scanf("%d %d", &id, &k);

        auto &tree_i = tree[id];
        tree_i = vector<int>(k+1);

        for (int j = 1; j <= k; ++j) {
            scanf("%d", &tree_i[j]);
        }
    }

    BFS(tree);

    return 0;
}
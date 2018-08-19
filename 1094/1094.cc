#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void BFS(const vector<vector<int>> &tree, 
         int root,
         int &population,
         int &level)
{
    population = 0;
    level = 1;

    queue<int> q;
    q.push(root);

    int l = 1;
    while (!q.empty()) {
        int p = 0;

        for (int i = 0, size = q.size(); i < size; ++i) {
            int parent = q.front();
            q.pop();

            ++p;

            for (auto c : tree[parent]) {
                q.push(c);
            }
        }

        if (p > population) {
            population = p;
            level = l;
        }

        ++l;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    vector<vector<int>> tree(n+1);
    vector<bool> appear(n+1, false);

    for (int i = 0; i < m; ++i) {
        int p, k;
        scanf("%d %d", &p, &k);

        auto &tree_p = tree[p];
        tree_p = vector<int>(k);

        for (int j = 0; j < k; ++j) {
            scanf("%d", &tree_p[j]);
            appear[tree_p[j]] = true;
        }
    }

    int root = 1;
    for (; root <= n && appear[root]; ++root);

    int population, level;
    BFS(tree, root, population, level);

    printf("%d %d\n", population, level);

    return 0;
}
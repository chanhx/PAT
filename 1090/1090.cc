#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void BFS(const vector<vector<int>> &tree,
         int root,
         double p,
         const double r,
         double &highest_price,
         int &count)
{
    highest_price = 0;
    count = 0;

    queue<int> q;
    q.push(root);

    while (!q.empty()) {
        for (int i = 0, size = q.size(); i < size; ++i) {
            auto s = q.front();
            q.pop();

            if (tree[s].size() == 0) {
                if (p > highest_price) {
                    highest_price = p;
                    count = 1;
                } else if (p == highest_price) {
                    ++count;
                }
            }

            for (auto ss : tree[s]) {
                q.push(ss);
            }
        }

        p *= r;
    }
}

int main()
{
    int n;
    double p, r;
    scanf("%d %lf %lf", &n, &p, &r);

    vector<vector<int>> tree(n);
    int root;
    for (int i = 0; i < n; ++i) {
        int supplier;
        scanf("%d", &supplier);

        if (supplier == -1) {
            root = i;
        } else {
            tree[supplier].push_back(i);
        }
    }

    double highest_price;
    int count;
    BFS(tree, root, p, 1+r/100, highest_price, count);

    printf("%.2f %d\n", highest_price, count);

    return 0;
}
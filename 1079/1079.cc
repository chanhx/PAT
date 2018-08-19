#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

inline void InputTree(vector<vector<int>> &tree, const int n)
{
    for (int i = 0; i < n; ++i) {
        auto &tree_i = tree[i];

        int k;
        scanf("%d", &k);

        if (k == 0) {
            int amount;
            scanf("%d", &amount);

            tree_i = {k, amount};
            continue;
        }

        tree_i = vector<int>(k+1);
        tree_i[0] = k;

        for (int j = 1; j <= k; ++j) {
            scanf("%d", &tree_i[j]);
        }
    }
}

double CalculateTotalSales(const vector<vector<int>> &tree, double p, const double r)
{
    double total_sales = 0;

    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        for (int i = 0, size = q.size(); i < size; ++i) {
            auto k = q.front();
            q.pop();

            auto node = tree[k];

            if (node[0] == 0) {
                total_sales += p * node[1];
                continue;
            }

            for (auto it = node.cbegin() + 1, end = node.cend();
                 it != end;
                 ++it)
            {
                q.push(*it);
            }
        }

        p *= r;
    }

    return total_sales;
}

int main()
{
    int n;
    double p, r;
    scanf("%d %lf %lf", &n, &p, &r);

    vector<vector<int>> tree(n);

    InputTree(tree, n);
    printf("%.1f\n", CalculateTotalSales(tree, p, 1 + r / 100));

    return 0;
}
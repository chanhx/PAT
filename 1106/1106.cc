#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void BFS(const vector<vector<int>> &tree, 
         double p, const double r,
         double &lowest, int &count)
{
    count = 0;

    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        for (int i = 0, size = q.size(); i < size; ++i) {
            auto n = q.front();
            q.pop();

            if (tree[n].empty()) {
                lowest = p;
                ++count;
                continue;
            }

            for (auto it = tree[n].cbegin()+1, end = tree[n].cend();
                 it != end;
                 ++it)
            {
                q.push(*it);
            }
        }

        if (count > 0) {break;}

        p *= r;
    }
}

int main()
{
    int n;
    double p, r;
    scanf("%d %lf %lf", &n, &p, &r);

    vector<vector<int>> tree(n);
    for (int i = 0; i < n; ++i) {
        auto &tree_i = tree[i];

        int k;
        scanf("%d", &k);

        if (k == 0) {continue;}

        tree_i = vector<int>(k+1);
        tree_i[0] = k;
        for (int j = 1; j <= k; ++j) {
            scanf("%d", &tree_i[j]);
        }
    }

    double lowest_price;
    int count;
    BFS(tree, p, 1+r/100, lowest_price, count);

    printf("%.4f %d\n", lowest_price, count);

    return 0;
}
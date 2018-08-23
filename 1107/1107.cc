#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int FindCluster(vector<int> &clusters, const int x)
{
    int c = x;
    for (; c != clusters[c]; c = clusters[c]);

    for (auto ix = x; ix != c;) {
        auto &cluster = clusters[ix];
        ix = cluster;
        cluster = c;
    }

    return c;
}

void Union(vector<int> &clusters, int a, int b)
{
    auto ca = FindCluster(clusters, a);
    auto cb = FindCluster(clusters, b);

    if (ca != cb) {
        clusters[ca] = cb;
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<int> clusters(n+1);
    unordered_map<int, int> hobbies_1st_p;

    for (int i = 1, k; i <= n; ++i) {
        clusters[i] = i;

        scanf("%d:", &k);

        for (int j = 0, h; j < k; ++j) {
            scanf("%d", &h);
            if (hobbies_1st_p.find(h) == hobbies_1st_p.cend()) {
                hobbies_1st_p[h] = i;
            } else {
                Union(clusters, i, hobbies_1st_p[h]);
            }
        }
    }

    unordered_map<int, int> root_clusters;
    vector<int> ids;

    for (int i = 1; i <= n; ++i) {
        auto c = FindCluster(clusters, i);
        if (root_clusters.find(c) == root_clusters.cend()) {
            root_clusters[c] = 0;
            ids.push_back(c);
        }
        ++root_clusters[c];
    }

    sort(ids.begin(), ids.end(),
         [&root_clusters](int a, int b) {
             return root_clusters[a] > root_clusters[b];
         });

    int size = root_clusters.size();

    printf("%d\n", size);
    for (int i = 0, end = size-1; i <= end; ++i) {
        printf("%d%c", root_clusters[ids[i]], i == end ? '\n' : ' ');
    }

    return 0;
}
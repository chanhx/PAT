#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    int n, m, l;
    scanf("%d %d", &n, &m);

    unordered_map<int, int> fav_colors;
    for (int i = 0; i < m; ++i) {
        int color;
        scanf("%d", &color);
        fav_colors[color] = i;
    }

    scanf("%d", &l);
    vector<int> colors(l);
    int num = 0;
    
    for (int i = 0; i < l; ++i) {
        int c;
        scanf("%d", &c);

        if (fav_colors.find(c) == fav_colors.cend()) {
            continue;
        }

        colors[num] = fav_colors[c];
        ++num;
    }

    int max_len = 0;
    vector<int> len(num, 0);
    for (int i = 0; i < num; ++i) {
        len[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (colors[j] <= colors[i] && len[j]+1 > len[i]) {
                len[i] = len[j] + 1;
            }
        }
        if (len[i] > max_len) {
            max_len = len[i];
        }
    }

    printf("%d\n", max_len);

    return 0;
}

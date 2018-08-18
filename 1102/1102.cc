#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int left, right;
};

void InOrderTravel(vector<Node> pv, int n, int &size)
{
    if (n < 0) {return;}

    InOrderTravel(pv, pv[n].right, size);
    --size;
    printf("%d%c", n, size > 0 ? ' ' : '\n');
    InOrderTravel(pv, pv[n].left, size);
}

void LevelOrderTravel(vector<Node> pv, int root)
{
    queue<int> q;
    q.push(root);

    int size = pv.size();

    while (!q.empty()) {
        auto n = q.front();
        q.pop();

        --size;
        printf("%d%c", n, size > 0 ? ' ' : '\n');

        int left = pv[n].left;
        int right = pv[n].right;

        if (right >= 0) {
            q.push(right);
        }
        if (left >= 0) {
            q.push(left);
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<Node> pv(n);
    vector<bool> appear(n, false);

    for (int i = 0; i < n; ++i) {
        char c1, c2;
        getchar();
        scanf("%c %c", &c1, &c2);

        int left = c1 == '-' ? -1 : c1 - '0';
        int right = c2 == '-' ? -1 : c2 - '0';

        pv[i] = {left, right};

        if (left >= 0) {
            appear[left] = true;
        }
        if (right >= 0) {
            appear[right] = true;
        }
    }

    int root = 0;
    for (; appear[root]; ++root);

    LevelOrderTravel(pv, root);

    int size = n;
    InOrderTravel(pv, root, size);

    return 0;
}
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void InorderTravel(const vector<int> &number,
                   vector <int> &cbt,
                   const int root,
                   const int size,
                   int &index)
{
    if (root > size) {
        return;
    }

    InorderTravel(number, cbt, root*2, size, index);
    cbt[root] = number[index];
    ++index;
    InorderTravel(number, cbt, root*2+1, size, index);
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<int> number(n);
    for (auto &n : number) {
        scanf("%d", &n);
    }
    sort(number.begin(), number.end());

    vector<int> cbt(n+1);
    int index = 0;
    InorderTravel(number, cbt, 1, number.size(), index);

    for (int i = 1; i <= n; ++i) {
        printf("%d%c", cbt[i], i == n ? '\n' : ' ');
    }

    return 0;
}
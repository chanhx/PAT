#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

inline int Lowbit(int x)
{
    return x & (-x);
}

void Update(vector<int> &c, int x, int v)
{
    for (int i = x, size = c.size(); i < size; i += Lowbit(i)) {
        c[i] += v;
    }
}

int CalculateSum(const vector<int> &c, const int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= Lowbit(i)) {
        sum += c[i];
    }

    return sum;
}

void PeekMedian(const vector<int> &c, const int size)
{
    int l = 1;
    for (int r = c.size(), k = (size+1)/2, mid; l < r; ) {
        mid = (l + r) / 2;

        if (CalculateSum(c, mid) >= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    printf("%d\n", l);
}

int main()
{
    int n;
    scanf("%d", &n);

    stack<int> s;
    vector<int> c(100005, 0);

    char instruction[15];
    for (int i = 0, num; i < n; ++i) {
        scanf("%s", instruction);

        if (instruction[1] == 'u') {                // Push
            scanf("%d", &num);
            s.push(num);
            Update(c, num, 1);
        } else if (instruction[1] == 'o') {         // Pop
            if (s.empty()) {
                printf("Invalid\n");
            } else {
                printf("%d\n", s.top());
                Update(c, s.top(), -1);
                s.pop();
            }
        } else {                                    // PeekMedian
            if (s.empty()) {
                printf("Invalid\n");
            } else {
                PeekMedian(c, s.size());
            }
        }
        
    }

    return 0;
}
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void PrintSequence(const vector<int> &seq)
{
    for (int i = 0, end = seq.size()-1; i <= end; ++i) {
        printf("%d%c", seq[i], i == end ? '\n' : ' ');
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<int> seq(n), partially_sorted_seq(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &seq[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &partially_sorted_seq[i]);
    }

    int i = 0, j;

    for (; i < n-1 && partially_sorted_seq[i] <= partially_sorted_seq[i+1]; ++i);
    for (j = i+1; j < n && partially_sorted_seq[j] == seq[j]; ++j);

    if (j >= n) {
        printf("Insertion Sort\n");
        sort(partially_sorted_seq.begin(), partially_sorted_seq.begin() + i + 2);
        PrintSequence(partially_sorted_seq);
    } else {
        printf("Heap Sort\n");

        make_heap(seq.begin(), seq.end());

        for (int i = n-1; i > 0; --i) {
            pop_heap(seq.begin(), seq.begin()+i+1);
            if (seq[i] != partially_sorted_seq[i]) {
                break;
            }
        }
        PrintSequence(seq);
    }
}
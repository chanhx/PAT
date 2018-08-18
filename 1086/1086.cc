#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

struct Node
{
    int data;
    struct Node *left, *right;
};

Node * BuildTree(vector<int> &pre, vector<int> &in,
                 int pre_begin, int pre_end,
                 int in_begin, int in_end)
{
    if (pre_end < pre_begin) {
        return nullptr;
    }

    auto node = new Node();

    int data = pre[pre_begin];
    node->data = data;

    int ii = in_begin;
    for (; ii <= in_end && in[ii] != data;) {++ii;}

    auto left_size = ii - in_begin;

    node->left = BuildTree(pre, in, 
                           pre_begin+1, pre_begin+left_size, 
                           in_begin, ii-1);

    node->right = BuildTree(pre, in, 
                            pre_begin+left_size+1, pre_end,
                            ii+1, in_end);

    return node;
}

void PostOrderTravel(Node *node, vector<int> &post, int &i)
{
    if (!node) {return;}

    PostOrderTravel(node->left, post, i);
    PostOrderTravel(node->right, post, i);

    post[i] = node->data;
    ++i;
}

int main()
{
    int n;
    scanf("%d", &n);

    stack<int> s;
    vector<int> pre(n);
    vector<int> in(n);

    char op[5];
    for (int i = 0, times = n*2, pre_i = 0, in_i = 0; i < times; ++i) {
        scanf("%s", op);

        if (op[1] == 'u') {
            int index;
            scanf("%d", &index);

            s.push(index);
            pre[pre_i] = index;
            ++pre_i;
        } else {
            in[in_i] = s.top();
            s.pop();
            ++in_i;
        }
    }

    auto root = BuildTree(pre, in, 0, n-1, 0, n-1);
    vector<int> post(n);

    int i = 0;
    PostOrderTravel(root, post, i);

    for (int i = 0; i < n; ++i) {
        if (i != 0) {printf(" ");}
        printf("%d", post[i]);
    }
    printf("\n");

    return 0;
}
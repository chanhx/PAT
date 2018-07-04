#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int data;
    struct Node *left, *right;
};

Node * BuildTree(int post_begin, int post_end, 
                 int in_begin, int in_end, 
                 vector<int> &post, vector<int> &in)
{
    if (post_begin > post_end) {
        return nullptr;
    }
    
    auto node = new Node();
    int data = post[post_end];
    node->data = data;

    int ii = in_begin;
    for (; ii < in_end && in[ii] != data; ++ii);

    node->left = BuildTree(post_begin, post_begin+ii-in_begin-1, 
                           in_begin, ii-1,
                           post, in);

    node->right = BuildTree(post_begin+ii-in_begin, post_end-1,
                            ii+1, in_end,
                            post, in);

    return node;
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<int> post(n), in(n);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", i == 0 ? &post[j] : &in[j]);
        }
    }

    auto root = BuildTree(0, n-1, 0, n-1, post, in);

    queue<Node *> level;
    level.push(root);

    while (true) {
        auto *node = level.front();
        level.pop();

        printf("%d", node->data);
        
        if (node->left) {
            level.push(node->left);
        }
        if (node->right) {
            level.push(node->right);
        }

        if (!level.empty()) {
            printf(" ");
        } else {
            printf("\n");
            break;
        }
    }

    return 0;
}

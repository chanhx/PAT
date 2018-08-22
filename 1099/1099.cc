#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

Node * InorderTravel(const vector<vector<int>> &tree,
                     const vector<int> &number,
                     const int root,
                     int &index)
{
    if (root == -1) {
        return nullptr;
    }

    auto node = new Node();

    auto &sub_trees = tree[root];

    node->left = InorderTravel(tree, number, sub_trees[0], index);

    node->data = number[index];
    ++index;

    node->right = InorderTravel(tree, number, sub_trees[1], index);

    return node;
}

void BFS(Node *root, int size)
{
    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        for (int i = 0, round_size = q.size(); i < round_size; ++i) {
            auto node = q.front();
            q.pop();

            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }

            --size;
            printf("%d%c", node->data, size == 0 ? '\n' : ' ');
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<vector<int>> tree(n, vector<int>(2));
    vector<int> number(n);

    for (auto &tree_i : tree) {
        scanf("%d %d", &tree_i[0], &tree_i[1]);
    }

    for (auto &num : number) {
        scanf("%d", &num);
    }
    sort(number.begin(), number.end());

    int index = 0;
    auto root = InorderTravel(tree, number, 0, index);

    BFS(root, n);

    return 0;
}
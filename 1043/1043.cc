#include <cstdio>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

void BSTInsert(Node *&root, const int v)
{
    if (root == nullptr) {
        root = new Node();
        root->data = v;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }

    if (v < root->data) {
        BSTInsert(root->left, v);
    } else {
        BSTInsert(root->right, v);
    }
}

void PreorderTravel(const Node *tree,
                    vector<int> &pre,
                    int &i,
                    const bool mirror)
{
    if (!tree) {return;}

    pre[i] = tree->data;
    ++i;

    auto &tree_left = mirror ? tree->right : tree->left;
    auto &tree_right = mirror ? tree->left : tree->right;

    PreorderTravel(tree_left, pre, i, mirror);
    PreorderTravel(tree_right, pre, i, mirror);
}

void PostorderPrint(const Node *tree, int &count, const bool mirror)
{
    if (!tree) {return;}

    auto &tree_left = mirror ? tree->right : tree->left;
    auto &tree_right = mirror ? tree->left : tree->right;

    PostorderPrint(tree_left, count, mirror);
    PostorderPrint(tree_right, count, mirror);

    --count;
    printf("%d%c", tree->data, count == 0 ? '\n' : ' ');
}

int main()
{
    int n;
    scanf("%d", &n);

    vector<int> pre(n);
    Node *tree = nullptr;

    for (auto &v : pre) {
        scanf("%d", &v);
        BSTInsert(tree, v);
    }

    vector<int> _pre(n);
    for (auto mirror : {false, true}) {
        int i = 0;
        PreorderTravel(tree, _pre, i, mirror);

        if (_pre == pre) {
            printf("YES\n");
            int size = pre.size();
            PostorderPrint(tree, size, mirror);
            return 0;
        }
    }

    printf("NO\n");

    return 0;
}
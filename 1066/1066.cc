#include <cstdio>
#include <algorithm>

using namespace std;

struct AVL
{
    int data;
    AVL *left, *right;

    AVL() = default;
    AVL(int d): data(d), left(nullptr), right(nullptr), height(1) {};

    static void Insert(AVL * &h, int data);

private:
    int height;
    static int Height(const AVL *node) {
        return node == nullptr ? 0 : node->height;
    }
    void UpdateHeight() {
        height = max(Height(left), Height(right)) + 1;
    }
    int balance_factor() {
        return Height(left) - Height(right);
    }
    static void RotateLeft(AVL * &node);
    static void RotateRight(AVL * &node);
};

void AVL::RotateLeft(AVL * &node)
{
    auto right = node->right;
    node->right = right->left;
    right->left = node;

    node->UpdateHeight();
    right->UpdateHeight();

    node = right;
}

void AVL::RotateRight(AVL * &node)
{
    auto left = node->left;
    node->left = left->right;
    left->right = node;

    node->UpdateHeight();
    left->UpdateHeight();

    node = left;
}

void AVL::Insert(AVL * &h, int data)
{
    if (h == nullptr) {
        h = new AVL(data);
        return;
    }

    if (data < h->data) {
        AVL::Insert(h->left, data);
        h->UpdateHeight();
        if (h->balance_factor() != 2) {
            return;
        }

        auto lbf = h->left->balance_factor();

        if (lbf == 1) {
            AVL::RotateRight(h);
        } else if (lbf == -1) {
            AVL::RotateLeft(h->left);
            AVL::RotateRight(h);
        }
    } else {
        AVL::Insert(h->right, data);
        h->UpdateHeight();
        if (h->balance_factor() != -2) {
            return;
        }

        auto rbf = h->right->balance_factor();

        if (rbf == -1) {
            AVL::RotateLeft(h);
        } else if (rbf == 1) {
            AVL::RotateRight(h->right);
            AVL::RotateLeft(h);
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    AVL *root = nullptr;

    for (int i = 0, data; i < n; ++i) {
        scanf("%d", &data);
        AVL::Insert(root, data);
    }

    printf("%d\n", root->data);

    return 0;
}
#include <iostream>

struct bTree
{
    int value;
    bTree *left, *right;

    bTree(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Пример обхода бинарного дерева в глубину
void iterBTree(bTree *root)
{
    if (root == nullptr)
    {
        return;
    }

    iterBTree(root->left);
    std::cout << root->value << std::endl;
    iterBTree(root->right);
}

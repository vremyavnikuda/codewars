/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#include <stdlib.h>

static int x0(struct TreeNode* root) {
    int z0 = 0;
    struct TreeNode* z1 = root;
    while (z1) {
        if (!z1->left) {
            z0++;
            z1 = z1->right;
        } else {
            struct TreeNode* z2 = z1->left;
            while (z2->right && z2->right != z1) {
                z2 = z2->right;
            }
            if (!z2->right) {
                z2->right = z1;
                z1 = z1->left;
            } else {
                z2->right = NULL;
                z0++;
                z1 = z1->right;
            }
        }
    }
    return z0;
}

static void x1(struct TreeNode* root, struct TreeNode** arr) {
    int z0 = 0;
    struct TreeNode* z1 = root;
    while (z1) {
        if (!z1->left) {
            arr[z0++] = z1;
            z1 = z1->right;
        } else {
            struct TreeNode* z2 = z1->left;
            while (z2->right && z2->right != z1) {
                z2 = z2->right;
            }
            if (!z2->right) {
                z2->right = z1;
                z1 = z1->left;
            } else {
                z2->right = NULL;
                arr[z0++] = z1;
                z1 = z1->right;
            }
        }
    }
}

static struct TreeNode* x2(struct TreeNode** arr, int l, int r) {
    if (l > r) {
        return NULL;
    }
    int z0 = (l + r) >> 1;
    struct TreeNode* z1 = arr[z0];
    z1->left = x2(arr, l, z0 - 1);
    z1->right = x2(arr, z0 + 1, r);
    return z1;
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    int z0 = x0(root);
    if (z0 == 0) {
        return NULL;
    }
    struct TreeNode** z1 = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * (size_t)z0);
    if (!z1) {
        return root;
    }
    x1(root, z1);
    struct TreeNode* z2 = x2(z1, 0, z0 - 1);
    free(z1);
    return z2;
}

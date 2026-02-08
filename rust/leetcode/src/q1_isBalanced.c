/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isBalanced(struct TreeNode *root) {
  int q(struct TreeNode * p) {
    if (!p)
      return 0;
    int a = q(p->left);
    if (a < 0)
      return -1;
    int b = q(p->right);
    if (b < 0)
      return -1;
    int d = a - b;
    if (d < 0)
      d = -d;
    if (d > 1)
      return -1;
    return (a > b ? a : b) + 1;
  }
  return q(root) >= 0;
}

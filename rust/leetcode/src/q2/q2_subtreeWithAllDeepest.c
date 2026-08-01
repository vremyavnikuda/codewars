/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
*/

struct TreeNode *ans;
int md;

int dfs(struct TreeNode *r, int d) {
  if (!r)
    return d;
  int l = dfs(r->left, d + 1);
  int ri = dfs(r->right, d + 1);
  if (l == ri && l >= md) {
    md = l;
    ans = r;
  }
  return l > ri ? l : ri;
}

struct TreeNode *subtreeWithAllDeepest(struct TreeNode *root) {
  ans = root;
  md = 0;
  dfs(root, 0);
  return ans;
}

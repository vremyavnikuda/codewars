/**
 * Definition for a binary tree node.
 */
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

static int s[10000];
static int sz;

void dfs(struct TreeNode *r, int i) {
  if (!r)
    return;
  if (sz == i) {
    s[sz++] = r->val;
  } else {
    s[i] += r->val;
  }
  dfs(r->left, i + 1);
  dfs(r->right, i + 1);
}

int maxLevelSum(struct TreeNode *root) {
  sz = 0;
  dfs(root, 0);
  int mx = -2147483648;
  int a = 0;
  for (int i = 0; i < sz; ++i) {
    if (mx < s[i]) {
      mx = s[i];
      a = i + 1;
    }
  }
  return a;
}

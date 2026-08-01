
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


static long long ts, ans;

long long dfs(struct TreeNode *r) {
  if (!r)
    return 0;
  long long t = r->val + dfs(r->left) + dfs(r->right);
  long long p = t * (ts - t);
  if (p > ans)
    ans = p;
  return t;
}

int maxProduct(struct TreeNode *root) {
  ans = 0;
  ts = dfs(root);
  ans = 0;
  dfs(root);
  return ans % 1000000007;
}

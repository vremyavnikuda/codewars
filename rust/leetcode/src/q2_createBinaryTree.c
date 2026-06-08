#include <stdlib.h>
struct TreeNode *createBinaryTree(int **descriptions, int descriptionsSize, int *descriptionsColSize)
{
    if (!descriptionsSize)
        return 0;
    int H = descriptionsSize * 2 + 1, i = 0, p, q, l, pi, ci;
    struct
    {
        struct TreeNode *n;
        int k;
        char c;
    } *t = calloc(H, sizeof(*t));
    while (i < descriptionsSize)
    {
        p = descriptions[i][0];
        q = descriptions[i][1];
        l = descriptions[i++][2];
        pi = (p % H + H) % H;
        ci = (q % H + H) % H;
        while (t[pi].k && t[pi].k != p)
            pi = (pi + 1) % H;
        if (!t[pi].k)
        {
            t[pi].k = p;
            t[pi].n = malloc(sizeof(struct TreeNode));
            t[pi].n->val = p;
            t[pi].n->left = t[pi].n->right = 0;
        }
        while (t[ci].k && t[ci].k != q)
            ci = (ci + 1) % H;
        if (!t[ci].k)
        {
            t[ci].k = q;
            t[ci].n = malloc(sizeof(struct TreeNode));
            t[ci].n->val = q;
            t[ci].n->left = t[ci].n->right = 0;
        }
        l ? (t[pi].n->left = t[ci].n) : (t[pi].n->right = t[ci].n);
        t[ci].c = 1;
    }
    for (i = 0; i < H; i++)
        if (t[i].k && !t[i].c)
            return t[i].n;
    return 0;
}

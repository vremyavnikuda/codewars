struct ListNode
{
    int val;
    struct ListNode *next;
};

int pairSum(struct ListNode *head)
{
    int m = 0;
    struct ListNode *s, *f, *p, *q, *r;
    for (s = head, f = head->next; f && f->next; s = s->next, f = f->next->next)
        ;
    for (p = s->next, q = 0; p; q = p, p = r)
        r = p->next, p->next = q;
    for (s = head; q; s = s->next, q = q->next)
        m = m > s->val + q->val ? m : s->val + q->val;
    return m;
}
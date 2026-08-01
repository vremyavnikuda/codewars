/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *deleteMiddle(struct ListNode *head)
{
    struct ListNode **a = &head, *b = head;
    for (; b && b->next; a = &(*a)->next, b = b->next->next)
        ;
    return *a = (*a)->next, head;
}

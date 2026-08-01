/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *rotateRight(struct ListNode *head, int k) {
  struct ListNode *a;
  int n;
  if (!(head && head->next && k))
    return head;
  for (a = head, n = 1; a->next; a = a->next, ++n) {
  }
  if (!(k %= n))
    return head;
  for (a->next = head, a = head; --n > k; a = a->next) {
  }
  return head = a->next, a->next = 0, head;
}

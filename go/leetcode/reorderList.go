//You are given the head of a singly linked-list. The list can be represented as:
//
//L0 → L1 → … → Ln - 1 → Ln
//Reorder the list to be on the following form:
//
//L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
//You may not modify the values in the list's nodes. Only nodes themselves may be changed.

package main

type ListNode struct {
	Val  int
	Next *ListNode
}

func reorderList(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}

	slow, fast := head, head
	for fast != nil && fast.Next != nil {
		slow = slow.Next
		fast = fast.Next.Next
	}

	var prev *ListNode
	curr := slow
	for curr != nil {
		nextTemp := curr.Next
		curr.Next = prev
		prev = curr
		curr = nextTemp
	}

	first, second := head, prev
	for second.Next != nil {
		// Store next nodes
		temp1 := first.Next
		temp2 := second.Next

		first.Next = second
		second.Next = temp1

		first = temp1
		second = temp2
	}

	return head
}
func main() {

}

package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	//указатель на первый узел нового списка, который мы будем формировать. Вначале он равен nil, так как список пуст.
	var result *ListNode = nil
	//temp: Временный указатель, который используется для создания нового узла и хранения текущего узла.
	//prev: Указатель на предыдущий узел в новом списке. Он необходим для соединения нового узла с предыдущим.
	var temp, prev *ListNode = nil, nil
	//carry: Переменная для хранения переноса, который возникает, если сумма значений двух узлов превышает 9. Изначально равен 0.
	carry := 0

	//Цикл сложения узлов
	for l1 != nil || l2 != nil {
		sum := carry

		if l1 != nil {
			sum += l1.Val
			l1 = l1.Next
		}

		if l2 != nil {
			sum += l2.Val
			l2 = l2.Next
		}

		carry = sum / 10
		sum = sum % 10

		temp = &ListNode{Val: sum}

		if result == nil {
			result = temp
		} else {
			prev.Next = temp
		}
		prev = temp
	}

	//Обработка остаточного процесса
	if carry > 0 {
		temp.Next = &ListNode{Val: carry}
	}

	//Выводим результат
	return result
}

// Если нужно вернуть пользователю результат
func printListNode(node *ListNode) {
	for node != nil {
		fmt.Println(node.Val)
		node = node.Next
	}
	fmt.Println()
}

func main() {

}

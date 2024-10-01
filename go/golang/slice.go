package main

import "fmt"

func main() {
	a := []int{1, 2, 3}
	b := make([]int, 3, 3)
	n := copy(b, a)

	fmt.Println("a = %v\n", a)
	fmt.Println("b = %v\n", b)
	fmt.Println("n = ", n)
}

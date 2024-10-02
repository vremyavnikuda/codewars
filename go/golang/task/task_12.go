package main

import "fmt"

func main() {
	var a int
	fmt.Scan(&a)

	if a < 1 {
		fmt.Println(-1)
		return
	}
	fib1, fib2 := 1, 1
	index := 2

	for fib2 < a {
		fibNext := fib1 + fib2
		fib1 = fib2

		fib2 = fibNext
		index++
	}

	if fib2 == a {
		fmt.Println(index)
	} else {
		fmt.Println(-1)
	}
}

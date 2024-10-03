package main

import (
	"fmt"
)

func main() {

	fmt.Println(fibonacci(4))
}

func fibonacci(n int) int {
	if n < 1 {
		return -1
	}
	if n == 1 || n == 2 {
		return 1
	}
	fib1, fib2 := 1, 1
	fibNext := 0

	for i := 3; i <= n; i++ {
		fibNext = fib1 + fib2
		fib1 = fib2
		fib2 = fibNext
	}
	return fibNext
}

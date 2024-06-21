package main

import (
	"fmt"
)

func digitalRoot(n int) int {
	if n < 10 {
		return n
	}

	sum := 0
	for n > 0 {
		sum += n % 10
		n /= 10
	}

	return digitalRoot(sum)
}

func main() {
	var n int
	fmt.Scan(&n)
	fmt.Println(digitalRoot(n))
}

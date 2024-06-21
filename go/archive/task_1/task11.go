package main

import (
	"fmt"
)

func main() {
	var a int
	var b int
	var c int
	fmt.Scan(&a)
	fmt.Scan(&b)

	a = a * a
	b = b * b
	c = a + b
	fmt.Print(c)
}

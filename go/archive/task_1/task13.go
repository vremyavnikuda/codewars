package main

import "fmt"

func main() {
	var a int
	fmt.Scan(&a)

	var b int
	b = a % 10
	fmt.Print(b)
}

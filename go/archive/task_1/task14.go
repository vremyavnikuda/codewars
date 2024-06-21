package main

import "fmt"

func main() {
	var a int
	fmt.Scan(&a)

	var b int = (a % 100) / 10
	fmt.Print(b)
}

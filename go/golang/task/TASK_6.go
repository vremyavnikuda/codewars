package main

import "fmt"

func main() {
	var a, b int
	fmt.Scan(&a, &b)
	var result float64
	result = float64(a+b) / 2
	fmt.Print(result)
}

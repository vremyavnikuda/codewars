package main

import "fmt"

func OfherAngle(a int, b int) int {
	return 180 - (a + b)
}
func main() {
	var a int
	var b int
	fmt.Scan(&a)
	fmt.Scan(&b)
	fmt.Print(OfherAngle(a, b))
}

package main

import "fmt"

func minimumFromFour() int {
	var a, b, c, d int
	fmt.Scanln(&a, &b, &c, &d)
	var minNumber int
	minNumber = min(a, b, c, d)
	return minNumber
}
func main() {
	minimumFromFour()
}

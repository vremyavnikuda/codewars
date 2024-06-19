package main

import "fmt"

func Between(a, b int) []int {

	var numberRange []int
	for i := a; i <= b; i++ {
		numberRange = append(numberRange, i)
	}
	return numberRange
}

func main() {
	a := 1
	b := 4
	fmt.Println(Between(a, b))
}

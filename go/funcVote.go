package main

import "fmt"

func vote(x int, y int, z int) int {
	variable := []int{x, y, z}
	counter := 0
	counter1 := 0
	for _, v := range variable {
		if v == 0 {
			counter++
		} else if v == 1 {
			counter1++
		}
	}
	var result int
	if counter > counter1 {
		result = 0
	} else {
		result = 1
	}
	return result
}

func main() {
	var x, y, z int

	fmt.Scanln(&x, &y, &z)
}

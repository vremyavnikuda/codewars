package main

import (
	"fmt"
	"math"
)

func main() {
	var lenght int
	fmt.Scan(&lenght)
	array := make([]int, lenght)

	min := math.MaxInt32
	count := 0
	for i := 0; i < lenght; i++ {
		fmt.Scanln(&array[i])
		if array[i] < min {
			min = array[i]
			count = 1
		} else if array[i] == min {
			count++
		}
	}
	fmt.Println(count)
}

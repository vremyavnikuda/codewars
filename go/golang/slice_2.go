package main

import "fmt"

func main() {
	array := [5]int{}
	var a int
	for i := 0; i < 5; i++ {
		fmt.Scan(&a)
		array[i] = a
	}
	var maxNumber int = array[0]
	for i := 1; i < len(array); i++ {
		if array[i] > maxNumber {
			maxNumber = array[i]
		}
	}
	fmt.Println(maxNumber)
}

package main

import "fmt"

func MinMax(arr []int) [2]int {
	min := arr[0]
	max := arr[0]
	for _, value := range arr[1:] {
		if value < min {
			min = value
		}
		if value > max {
			max = value
		}
	}
	return [2]int{min, max}
}

func main() {
	arr := []int{3, 2, 1, 4, 5}
	result := MinMax(arr)
	fmt.Println(result)
}

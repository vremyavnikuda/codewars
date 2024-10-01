package main

import "fmt"

func main() {
	var lenghtArray int
	fmt.Scanln(&lenghtArray)
	array := make([]int, lenghtArray)
	for i := 0; i < lenghtArray; i++ {
		fmt.Scan(&array[i])
	}

	for inx, item := range array {
		if inx%2 == 0 {
			fmt.Print(item, " ")
		}
	}
}

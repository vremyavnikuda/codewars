package main

import "fmt"

func main() {
	var lenght int
	fmt.Scan(&lenght)
	count := 0
	array := make([]int, lenght)

	if len(array) == 1 {
		fmt.Println(1)
	}

	for i := 0; i < lenght; i++ {
		fmt.Scan(&array[i])
		if array[i] > 0 {
			count++
		}
	}
	fmt.Println(count)
}

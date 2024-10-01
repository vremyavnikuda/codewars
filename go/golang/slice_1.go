package main

import "fmt"

func main() {
	var n int
	fmt.Scanln(&n)
	resultSlice := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&resultSlice[i])
	}
	fmt.Println(resultSlice[3])
}

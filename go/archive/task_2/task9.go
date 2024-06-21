package main

import "fmt"

func main() {
	var a, b int
	fmt.Scan(&a, &b)

	maxNum := maxNumber(a, b)
	if maxNum == -1 {
		fmt.Println("NO")
	} else {
		fmt.Println(maxNum)
	}
}

func maxNumber(a int, b int) int {
	for i := b; i >= a; i-- {
		if i%7 == 0 {
			return i
		}
	}
	return -1
}

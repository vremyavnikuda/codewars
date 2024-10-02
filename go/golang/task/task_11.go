package main

import (
	"fmt"
)

func main() {
	var number int
	result := 1
	fmt.Scan(&number)
	if number != 0 {
		for i := 0; i <= number; i++ {
			i = result + result
			fmt.Print(result, " ")
			result = i
		}
	}
	if result <= number {
		fmt.Println(result)
	}
}

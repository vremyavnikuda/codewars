package main

import (
	"fmt"
	"strconv"
)

func main() {
	var number int
	fmt.Scan(&number)

	digits := make(map[rune]bool)
	for _, digit := range strconv.Itoa(number) {
		if _, exists := digits[digit]; exists {
			fmt.Println("NO")
			return
		}
		digits[digit] = true
	}
	fmt.Println("YES")
}

package main

import (
	"fmt"
	"strconv"
)

func main() {
	var number, deleteNumber int

	fmt.Scan(&number)
	fmt.Scan(&deleteNumber)

	stringNumber := strconv.Itoa(number)
	var result string
	for _, char := range stringNumber {
		if char != rune(deleteNumber+48) {
			result += string(char)
		}
	}
	if result != "" {
		fmt.Println(result)
	} else {
		fmt.Println(0)
	}
}

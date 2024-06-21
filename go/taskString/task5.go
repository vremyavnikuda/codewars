package main

import (
	"fmt"
)

func main() {
	var input string
	fmt.Println("Введите строку:")
	fmt.Scanln(&input)

	output := removeDuplicates(input)
	fmt.Println(output)
}

func removeDuplicates(s string) string {
	var result string
	seen := make(map[rune]int)

	for _, char := range s {
		seen[char]++
	}

	for _, char := range s {
		if seen[char] == 1 {
			result += string(char)
		}
	}

	return result
}

package main

import (
	"fmt"
	"strings"
)

func main() {
	var number string
	var digit rune
	fmt.Scanln(&number)
	fmt.Scanf("%c", &digit)

	result := strings.ReplaceAll(number, string(digit), "")
	fmt.Println(result)
}

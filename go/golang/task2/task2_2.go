package main

import (
	"fmt"
)

func main() {
	var str string
	fmt.Scan(&str)

	//result
	fmt.Println(maxDigitNumber(str))
}

func maxDigitNumber(str string) string {
	maxDigit := '0'
	for _, elem := range str {
		if elem > maxDigit {
			maxDigit = elem
		}
	}
	return string(maxDigit)
}

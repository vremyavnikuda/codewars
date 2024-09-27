package main

import (
	"fmt"
	"strconv"
	"unicode"
)

func main() {
	a := "%^80"
	b := "hhhhh20&&&&nd"
	result := adding(a, b)
	fmt.Println(result)
}

func adding(a, b string) int64 {
	var numStr1, numStr2 string

	// Извлечение чисел из первой строки
	for _, char := range a {
		if unicode.IsDigit(char) {
			numStr1 += string(char)
		}
	}

	// Извлечение чисел из второй строки
	for _, char := range b {
		if unicode.IsDigit(char) {
			numStr2 += string(char)
		}
	}

	// Преобразование строк в числа и их суммирование
	num1, err1 := strconv.Atoi(numStr1)
	if err1 != nil {
		fmt.Println(err1)
	}
	num2, err2 := strconv.Atoi(numStr2)
	if err2 != nil {
		fmt.Println(err2)
	}

	return int64(num1 + num2)
}

package main

import (
	"fmt"
	"strings"
)

func main() {
	var input string
	fmt.Scanln(&input)

	// Убираем символ новой строки
	input = strings.TrimSpace(input)

	// Инициализируем переменную для хранения максимальной цифры
	maxDigit := '0'

	// Проходим по каждому символу строки
	for _, char := range input {
		if char > maxDigit {
			maxDigit = char
		}
	}

	// Печатаем результат
	fmt.Println(string(maxDigit))
}

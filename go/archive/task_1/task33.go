package main

import (
	"fmt"
	"strconv" // Импортируем пакет strconv для преобразования чисел в строки
)

func main() {
	// Объявляем две переменные num1 и num2 типа int
	var num1, num2 int

	// Считываем значения num1 и num2 с консоли
	fmt.Scan(&num1, &num2)

	// Преобразуем num1 и num2 в строки num1Str и num2 -> Str
	num1Str := strconv.Itoa(num1)
	num2Str := strconv.Itoa(num2)

	// Перебираем каждую цифру num1Str
	for _, digit := range num1Str {
		// Если digit содержится в num2Str, выводим её
		if contains(num2Str, byte(digit)) {
			fmt.Printf("%c ", digit)
		}
	}
}

// Функция contains проверяет, содержит ли строка s символ b
func contains(s string, b byte) bool {
	// Перебираем каждую цифру в строке s
	for i := 0; i < len(s); i++ {
		// Если сравниваемый символ равен b, возвращаем true
		if s[i] == b {
			return true
		}
	}
	// Если ни один из символов не равен b, возвращаем false
	return false
}

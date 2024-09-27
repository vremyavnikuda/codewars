package main

import (
	"fmt"
	"strconv"
)

func main() {
	// Анонимная функция, которая получает число.
	// Возвращает только четные числа из полученного uint.
	fn := func(number uint) uint {
		var result string

		// Преобразуем число в строку для итерации по цифрам
		numberStr := strconv.Itoa(int(number))

		for _, digitRune := range numberStr {
			digit := int(digitRune - '0')
			// Проверяем, является ли цифра четной (но не 0)
			if digit%2 == 0 && digit != 0 {
				result += strconv.Itoa(digit)
			}
		}

		// Если результат пустой, возвращаем 100
		if result == "" {
			return 100
		}

		// Преобразуем строку результата обратно в uint
		resultNumber, _ := strconv.Atoi(result)
		return uint(resultNumber)
	}
	fmt.Println(fn(123344))
}

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	// Получаем пользовательский ввод данных
	scanner.Scan()
	s := scanner.Text()
	// Удаляем пробелы
	s = strings.ReplaceAll(s, " ", "")
	// Заменяем запятые на точки
	s = strings.ReplaceAll(s, ",", ".")
	// Делим строку по разделителю
	arr := strings.Split(s, ";")
	if len(arr) != 2 {
		return
	}
	// Конвертируем строчные значения в числа с плавающей точкой
	number1, err1 := strconv.ParseFloat(arr[0], 64)
	number2, err2 := strconv.ParseFloat(arr[1], 64)
	if err1 != nil || err2 != nil {
		fmt.Println(err1, err2)
		return
	}
	// Выполняем операцию и выводим результат
	if number1 == 0 {
		return
	}
	result := number1 / number2
	fmt.Printf("%.4f\n", result)
}

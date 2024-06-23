package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var number int
	fmt.Scanln(&number)
	fmt.Println(numberSquared(number))
}

func numberSquared(number int) int {
	if number < 0 {
		return 0
	}

	inputString := strconv.Itoa(number)
	var builderString strings.Builder

	//перебираем строку числе и возводим в квадрат каждое число и формируем строку числового ряда
	for _, char := range inputString {
		digit := char - '0'
		square := int(digit * digit)
		builderString.WriteString(fmt.Sprintf("%d", square))
	}

	//преобразовываем строку чисел -> в числовой ряд
	result, err := strconv.Atoi(builderString.String())
	if err != nil {
		return 0
	}
	return result
}

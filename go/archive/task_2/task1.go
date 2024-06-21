package main

import (
	"fmt"
)

func main() {
	var number int
	fmt.Scan(&number)

	// Преобразует чисто в отдельные данные
	digit1 := number % 10
	digit2 := (number / 10) % 10
	digit3 := number / 100

	// Собираем чисто и переворачиваем его 
	reversed := digit1*100 + digit2*10 + digit3

	fmt.Println(reversed)
}

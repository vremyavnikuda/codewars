package main

import "fmt"

func main() {
	Decode("MDCLXVI")
	Divisors(12)
}

// Написать функцию, которая принимает на вход римскую цифру и возвращает ее значение
func Decode(roman string) int {
	// карта значений римских цифр
	romanMap := map[byte]int{
		'I': 1,
		'V': 5,
		'X': 10,
		'L': 50,
		'C': 100,
		'D': 500,
		'M': 1000,
	}

	total := 0
	prevValue := 0

	// перебираем римскую цифру
	for i := len(roman) - 1; i >= 0; i-- {
		value := romanMap[roman[i]]

		if value < prevValue {
			total -= value
		} else {
			total += value
		}
		prevValue = value
	}
	fmt.Println(total)
	return total
}

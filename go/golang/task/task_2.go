package main

import "fmt"

func main() {
	var number int
	var reversDigit int
	fmt.Scan(&number)
	for number > 0 {
		lastDigit := number % 10
		reversDigit = reversDigit*10 + lastDigit
		number = number / 10
	}
	fmt.Println(reversDigit)
}

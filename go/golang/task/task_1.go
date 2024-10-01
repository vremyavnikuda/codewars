package main

import "fmt"

func main() {
	var number int
	sum := 0
	fmt.Scan(&number)
	for number > 0 {
		lastDigit := number % 10
		sum += lastDigit
		number = number / 10
	}
	fmt.Println(sum)
}

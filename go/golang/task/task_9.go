package main

import "fmt"

func main() {
	var number int
	fmt.Scan(&number)
	for number > 9 {
		sum := 0
		for number > 0 {
			sum += number % 10
			number /= 10
		}
		number = sum
	}
	fmt.Println(number)
}

package main

import "fmt"

func sumInt(args ...int) (count int, sum int) {
	//кол-во аргументов
	count = len(args)
	//сумма аргументов
	sum = 0

	for _, numbers := range args {
		sum += numbers
	}
	return count, sum
}

func main() {
	a, b := sumInt(1, 0)
	fmt.Println(a, b)
}

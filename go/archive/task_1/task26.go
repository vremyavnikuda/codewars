package main

import "fmt"

func main() {
	var num int
	fmt.Scan(&num)

	sum := 0
	for i := 0; i < num; i++ {
		var number int
		fmt.Scan(&number)
		if number >= 10 && number <= 99 && number%8 == 0 {
			sum += number
		}
	}
	fmt.Println(sum)
}

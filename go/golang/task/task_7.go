package main

import "fmt"

func main() {
	var lenght int
	fmt.Scan(&lenght)
	var number int
	var count int
	for i := 0; i < lenght; i++ {
		fmt.Scanln(&number)
		if number == 0 {
			count++
		}
	}
	fmt.Println(count)
}

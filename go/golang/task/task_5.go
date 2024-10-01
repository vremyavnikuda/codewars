package main

import "fmt"

func main() {
	var a, b, c int
	flag := false
	fmt.Scan(&a, &b, &c)

	if ((a + b) > c) && ((a + c) > b) && ((b + c) > a) {
		flag = true
	} else {
		flag = false
	}
	if flag {
		fmt.Println("Существует")
	} else {
		fmt.Println("Не существует")
	}
}

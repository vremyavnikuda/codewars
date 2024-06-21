package main

import "fmt"

func main() {
	var number int
	switch number {
	case 0:
		fmt.Println("i равно 0")
	case 1:
		fmt.Println("i равно 1")
	case 2:
		fmt.Println("i равно 2")
	default:
		fmt.Println("i не равно 0, 1 или 2")
	}
}

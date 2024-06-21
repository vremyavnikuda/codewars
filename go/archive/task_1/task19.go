package main

import "fmt"

func main() {
	var a int
	fmt.Scan(&a)

	if a > 0 {
		fmt.Print("Число положительное")
	} else if a < 0 {
		fmt.Print("Число отрицательное")
	} else {
		fmt.Print("Ноль")
	}
}

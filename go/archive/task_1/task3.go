package main

import "fmt"

func main() {
	var a int = 31
	var b int = 14

	// равно
	fmt.Println(a == b) // выведет false

	// не равно
	fmt.Println(a != b) // выведет true

	// больше чем
	fmt.Println(a > b) // выведет true

	// больше или равно
	fmt.Println(a >= b) // выведет true

	// меньше чем
	fmt.Println(a < b) // выведет false

	// меньше или равно
	fmt.Println(a <= b) // выведет false
}

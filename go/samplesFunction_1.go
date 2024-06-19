package main

import "fmt"

/*Samples easy function*/
func add(x int, y int) {
	z := x + y
	fmt.Println(z)
}
func addIntAndFloat(x, y int, a, b, c float32) float32 {
	z := float32(x) + float32(y) + a + b + c
	fmt.Println(z)
	return z
}

func fn() (int, error) {
	// Какая-то полезная работа
	// ...
	return 0, nil
}
func ExampleIgnor() {
	fn()

	i, _ := fn()
	fmt.Println(i)

	_, err := fn()
	if err == nil {
		fmt.Println("Ошибок нет")
	}
}

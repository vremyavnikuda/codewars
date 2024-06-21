package main

import "fmt"

func main() {
	a := 8
	b := 5
	println(a % b)

	var x = 12 / 5
	println(x)

	var a int = 31
	var b int = 14
	//--------------
	a += b
	fmt.Println(a) // выведет 45
	//--------------
	a -= b
	fmt.Println(a) // выведет 17
	//--------------
	a *= b
	fmt.Println(a) // выведет 434
	//--------------
	a /= b
	fmt.Println(a) // выведет 2
	//--------------
	a %= b
	fmt.Println(a) // выведет 3

	x := 9
	y := 4
	println(x > y || x == y)
}

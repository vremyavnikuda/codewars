package main

import "fmt"

func main() {
	x := func(fn func(i int) int, i int) func(int) int { return fn }(func(i int) int { return i + 1 }, 5)
	fmt.Printf("%T\n", x)

	fmt.Println(Add(2, 3))
}

func Add(x int, y int) (result int) {
	result = x + y
	return result
}

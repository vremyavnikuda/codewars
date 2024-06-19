package main

import "fmt"

func changer(i *int) {
	*i = 2 * *i
}

func main() {
	i := 11
	changer(&i)
	println(i)
	x1 := 2
	x2 := 4
	test(&x1, &x2)
	test1(&x1, &x2)

}

func test(x1 *int, x2 *int) {
	var sum = *x1 * *x2
	fmt.Println(sum)
}
func test1(x1 *int, x2 *int) {
	*x1, *x2 = *x2, *x1
	fmt.Println(*x1, *x2)
}

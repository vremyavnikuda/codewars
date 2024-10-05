package main

import "fmt"

func main() {
	MyPrint(1, 2, 3, 4, 5)
	x := 5
	zero(&x)
	fmt.Println(x)
	fmt.Println("====================")
	i := 11
	changer(&i)
	fmt.Println(i)
}

func MyPrint(a ...interface{}) {
	for _, elem := range a {
		fmt.Printf("%d", elem)
	}
	fmt.Println("---------------------")
}
func zero(x *int) {
	*x = 100
}
func changer(i *int) {
	*i = 2 * *i
}

// считайте что fmt уже импортирован и main объявлен
func test(x1 *int, x2 *int) {
	i := *x1 * *x2
	fmt.Println(i)
}

func remove(x1 *int, x2 *int) {
	*x1, *x2 = *x2, *x1
	fmt.Println(*x1, *x2)
}

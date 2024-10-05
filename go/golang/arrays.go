package main

import "fmt"

func main() {
	arrays()
	fmt.Println("-----------")
	initArray()
}

func arrays() {
	a := [...]int{1, 2, 3}
	b := [3]int{3, 4, 5}
	println(a)
	println(b)
}

func println(a [3]int) {
	for idx, elem := range a {
		//idx -> индекс массива
		//elm -> элемент массива
		fmt.Println(idx, "->", elem)
	}
}
func initArray() {
	var a [3]int = [3]int{1, 2, 3}
	b := [3]int{1, 2, 3}
	c := [...]int{1, 2, 3}
	d := [3]int{1: 12}
	fmt.Println(a)
	fmt.Println(b)
	fmt.Println(c)
	fmt.Println(d == c)
}

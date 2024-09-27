package main

import "fmt"

func myFuncPrintln(a ...interface{}) {
	for _, elem := range a {
		fmt.Println(elem)
	}
}

func exampleMyPrint() {
	myFuncPrintln(1, 2, 3, 4, 5)
}
func main() {
	exampleMyPrint()
	ExampleExpandSile1()
	ExampleExpandSile2()
}

func ExampleExpandSile1() {
	s := []interface{}{1, 2, 3, 4, 5}
	fmt.Println(s)
	fmt.Println(s...)
}

func ExampleExpandSile2() {
	s1 := []interface{}{1, 2, 3, 4, 5}
	s2 := []interface{}{6, 7, 8, 9, 10}

	s1 = append(s1, s2...)

	fmt.Println(s1...)
}

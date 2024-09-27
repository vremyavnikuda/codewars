package main

import "fmt"

func scope() {
	v := 1
	fmt.Println(v)
}

func main() {
	scope()
	ExampleScope()
	ExampleScope2()
}

func ExampleScope() {
	var v int = 1
	{
		var v string = "2 = type string"
		fmt.Println(v)
	}
	fmt.Println(v)
}
func ExampleScope2() {
	var i string = "string"

	for i := 0; i < 1; i++ {
		fmt.Println(i)
	}

	for i := 0; i < 1; i++ {
		i := true
		fmt.Println(i)
	}

	fmt.Println(i)
}

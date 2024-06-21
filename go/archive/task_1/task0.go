package main

import "fmt"

func main() {
	fmt.Println("Hello, World!")
	x := 12
	println(x)

	var a int = 32
	var b int = 14
	var result int

	//+
	result = a + b
	println(result)

	//-
	result = a - b
	println(result)

	//*
	result = a * b
	println(result)

	// :
	result = a / b
	println(result)

	// %
	result = a % b
	println(result)
	hello()
	helloX3()

}

func hello() {
	println("I like Go!")
}
func helloX3() {
	fmt.Println("I like Go!")
	fmt.Println("I like Go!")
	fmt.Println("I like Go!")
}

func variable() {

}

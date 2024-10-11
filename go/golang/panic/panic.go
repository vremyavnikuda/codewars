package main

import "fmt"

func main() {
	defer saveData()
	fmt.Println("Программа работает: ")
	test(0)
}
func test(a uint8) {
	if a == 0 {
		panic("a==0: ")
	}
}

func saveData() {
	fmt.Println("Save data")
}

package main

import "fmt"

func main() {
	a := "12"
	c := 100
	b := []byte(a)
	a += string(b)
	fmt.Println(c + b)
}

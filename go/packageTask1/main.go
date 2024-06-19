package main

import (
	"fmt"
	"packageTask1/test"
)

func main() {
	a := 100
	LetsGo(a)
	fmt.Print(a, " ")
	test.LetsGo(a)
}

func LetsGo(b int) {
	b++
}

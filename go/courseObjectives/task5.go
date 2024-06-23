package main

import "fmt"

func main() {
	v := 5
	p := &v
	fmt.Print(*p, " ")
	changePointer(p)
	fmt.Print(*p)
}

func changePointer(p *int) {
	v := 3
	p = &v
}
